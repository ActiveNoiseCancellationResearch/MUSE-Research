
ui_cfg_1;                       % Reads undesired input data into array ui_data
di_cfg_1;
mic_cfg_1;
ls_cfg_1;                       % config file #1 for loudspeaker, sets array coeffs
hs_cfg_1;                       % config file #1 for headphone, sets array coeffs
ra_cfg_1;                       % config file #1 to set values that are fed into room_acoustics_to_coeffs
room_acoustics_to_coeffs(Qi, ri, fs);       % sets array of coeffs for room acoustics 
