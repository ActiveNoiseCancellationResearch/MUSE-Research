close all
clear
clc

master_cfg_1;

n_samps = min(100000,numel(ui_data));
ls_model = ANC_Filter(ls_coeffs);                                       % instantiates a new filter as ls_model
hs_model = ANC_Filter(hs_coeffs);                                       % instantiates a new filter as hs_model
mic_model = ANC_Filter(mic_coeffs);
ra_coeffs = room_acoustics_to_coeffs(Qi, ri, ui_fs);
ra_model = ANC_Filter(ra_coeffs);                                       % instantiates a new filter as ra_model
canceller = ANC_Canceller(canc_filter_order, canc_mu, probes_list, n_samps, mic_coeffs, hs_coeffs);
e = zeros(size(ui_data));
err = zeros(size(ui_data));
x__ = zeros(size(ui_data));                                             % initialize each element in the system to an
x_ = zeros(size(ui_data));                                              % array full of zeros, with length  of the array
y = zeros(size(ui_data));                                               % set to the size of the undesired signal
c = zeros(size(ui_data));
d = zeros(size(ui_data));
e_ = zeros(size(ui_data));
for n=1:n_samps
    x__(n) = ls_model.new_sample(ui_data(n));
    x_(n) = ra_model.new_sample(x__(n));
    y(n) = canceller.new_sample(ui_data(n));
    c(n) = hs_model.new_sample(y(n));
    d(n) = di_data(n);
    e(n) = x_(n) + d(n) + c(n);
    err(n) = x_(n) + c(n);
    e_(n) = mic_model.new_sample(e(n));
    canceller.coeff_update(e_(n));
    if mod(n,1000) == 0
        disp(n)
    end
end

sse = conv(ones(100,1)/100,err.^2);

% audiowrite('output_e.wav',ui_data,ui_fs);

subplot (4,2,1)
plot(ui_data)
title('ui_data')

subplot (4,2,2)
plot(e)
title('e')

subplot (4,2,3)
plot(sse)
title('sse')

subplot (4,2,4)
plot(x_)
title('x_')

subplot (4,2,5)
plot(y)
title('y')

subplot (4,2,6)
plot(c)
title('c')

subplot (4,2,7)
plot(d)
title('d')

subplot (4,2,8)
plot(e_)
title('e_')


