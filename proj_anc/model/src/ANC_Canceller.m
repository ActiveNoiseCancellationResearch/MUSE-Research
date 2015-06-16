classdef ANC_Canceller < handle
    properties
        in_filter_order;
        in_mu;
        mic_model;
        hs_model;
        current_output;
        update_output;
        model_coeffs;
        recent_samps_in;
        recent_samps_v;
        
    end
    methods
        function cancel_constructor = ANC_Canceller(filter_order, mu, mic_coeffs, hs_coeffs)
            cancel_constructor.in_filter_order = filter_order;
            cancel_constructor.in_mu = mu;
            cancel_constructor.mic_model = ANC_Filter(mic_coeffs);
            cancel_constructor.hs_model = ANC_Filter(hs_coeffs);
            cancel_constructor.model_coeffs = zeros(1,filter_order);
            cancel_constructor.model_coeffs(1) = 1;
            cancel_constructor.recent_samps_in = zeros(1,filter_order);
            cancel_constructor.recent_samps_v = zeros(1,filter_order);
            
        end
        function current_output = new_sample(my_canceller,input_samp)
            my_canceller.recent_samps_in(2:end) = my_canceller.recent_samps_in(1:end-1);    % deletes last value in array
            my_canceller.recent_samps_in(1) = input_samp;                                   % adds input_samp to array
            current_output = my_canceller.recent_samps_in*my_canceller.model_coeffs';       % sum of products
            temp = my_canceller.hs_model.new_sample(input_samp);                            % cascaded hs_model filter
            v = my_canceller.mic_model.new_sample(temp);                                    % into mic_model filter
            my_canceller.recent_samps_v(2:end) = my_canceller.recent_samps_v(1:end-1);
            my_canceller.recent_samps_v(1) = v;
        end
        function coeff_update(my_canceller, e)
            for i = 1:my_canceller.in_filter_order
                my_canceller.model_coeffs(i) = my_canceller.model_coeffs(i) - my_canceller.in_mu...
                    * e * my_canceller.recent_samps_v(i);
            end
        end
    end
end
   
 