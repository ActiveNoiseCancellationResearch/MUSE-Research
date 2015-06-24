
ui_cfg_1;                                                           % Reads undesired input data into array ui_data
di_cfg_1;
% ui_data = randi([-1,1],50000,1);
% ui_fs = 20000;
[ui_data,ui_fs] = audioread(ui_filename);                           % reading .wav file as undesired sound
ui_data = ui_data(:,1);
[di_data,di_fs] = audioread(di_filename);                           % reading .wav file as desired sound
di_data = di_data(:,1);
mic_cfg_1;
ls_cfg_1;                                                           % config file #1 for loudspeaker, sets array coeffs
hs_cfg_1;                                                           % config file #1 for headphone, sets array coeffs
ra_cfg_1;                                                           % config file #1 to set values that are fed into room_acoustics_to_coeffs
room_acoustics_to_coeffs(Qi, ri, ui_fs);                            % sets array of coeffs for room acoustics 
canceller_cfg_1;


