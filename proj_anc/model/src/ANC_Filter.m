classdef ANC_Filter < handle
  properties
        %current_output;
        model_coeffs;
        recent_samps;
  end
  methods
        function my_constructor = ANC_Filter(coeffs)
            my_constructor.model_coeffs = coeffs;
            my_constructor.recent_samps = zeros(size(coeffs));
        end
        function current_output = new_sample(my_filter,input_samp)
            my_filter.recent_samps(2:end) = my_filter.recent_samps(1:end-1);  % deletes last value in array 
            my_filter.recent_samps(1) = input_samp;                           % adds input_samp to array
            current_output = my_filter.recent_samps*my_filter.model_coeffs';  % sum of products
            %disp(current_output); 
        end
 end
 end
    