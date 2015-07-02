close all
clear
clc

master_cfg_nrefls6_rmax1_mu01_fltord150_norm;

% ui_data = randi([-1,1],50000,1);                                  % for random noise testing
% ui_fs = 20000;

[ui_data,ui_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', ui_filename));  % reading .wav file as undesired sound
ui_data = ui_data(:,1);
[di_data,di_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', di_filename));  % reading .wav file as desired sound
di_data = di_data(:,1);
n_samps = min(660000,numel(ui_data));  

ls_model = ANC_Filter(ls_coeffs);                                       % instantiates a new filter as ls_model
hs_model = ANC_Filter(hs_coeffs);                                       % instantiates a new filter as hs_model
mic_model = ANC_Filter(mic_coeffs);
ra_coeffs = room_acoustics_to_coeffs(Qi, ri, ui_fs);
ra_model = ANC_Filter(ra_coeffs);                                       % instantiates a new filter as ra_model
canceller = ANC_Canceller(canc_filter_order, canc_mu, probes_list, norm, n_samps, mic_coeffs, hs_coeffs);

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
    if mod(n,10000) == 0
        disp(n)
        plot_probes(canceller);
    end
end

sse = conv(ones(100,1)/100,err.^2);

audiowrite('output_e.wav',e,ui_fs);                     
figure;
a = subplot (4,2,1);
plot(ui_data)
title('ui_data')

subplot (4,2,2);
plot(e)
title('e')

subplot (4,2,3);
plot(sse)
title('sse')

subplot (4,2,4);
plot(x_)
title('x_')

subplot (4,2,5);
plot(y)
title('y')

subplot (4,2,6);
plot(c)
title('c')

subplot (4,2,7);
plot(d)
title('d')

subplot (4,2,8);
plot(e_)
title('e_')

saveas(a, 'varietygraph.png')

plot_probes(canceller);
save_probe_plot(canceller)



