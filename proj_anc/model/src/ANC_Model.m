clear
clc

master_cfg_1;
[ui_data,ui_fs] = audioread(ui_filename);                           % reading .wav file
[di_data,di_fs] = audioread(di_filename);
ls_model = ANC_Filter(ls_coeffs);                                   % instantiates a new filter as ls_model
hs_model = ANC_Filter(hs_coeffs);                                   % instantiates a new filter as hs_model
mic_model = ANC_Filter(mic_coeffs);                             
ra_coeffs = room_acoustics_to_coeffs(Qi, ri, fs);
ra_model = ANC_Filter(ra_coeffs);                                   % instantiates a new filter as ra_model
canceller = ANC_Canceller(canc_filter_order, canc_mu, mic_coeffs, hs_coeffs);
e = zeros(size(ui_data));
for n=1:size(ui_data)
    x__ = ls_model.new_sample(ui_data(n));
    x_ = ra_model.new_sample(x__);
    y = canceller.new_sample(x_);
    c = hs_model.new_sample(y);
    d = di_data(n);
    e(n) = x_ + d + c;
    e_ = mic_model.new_sample(e(n));
    canceller.coeff_update(e_);
    if mod(n,1000) == 0
        disp(n)
    end
end

audiowrite('output_e.wav',ui_data,ui_fs);

subplot (2,1,1)
plot(ui_data)
subplot (2,1,2)
plot(e)
