close all
clear
clc

addpath(genpath('C:\Users\Julie\Desktop\MUSE-Research\proj_anc\model\cfg'));
addpath(genpath('C:\Users\Julie\Desktop\MUSE-Research\proj_anc\model\src'));

ui_cfg_1;                                                           
di_cfg_1;
ls_cfg_max1_n2;                                                                                                                 
ra_cfg_nrefls6_rmax1;                                                  

[ui_data,ui_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', ui_filename)); 
ui_data = ui_data(:,1);
[di_data,di_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', di_filename)); 
di_data = di_data(:,1);

ls_model = ANC_Filter(ls_coeffs);
ra_coeffs = room_acoustics_to_coeffs(Qi, ri, ui_fs);
ra_model = ANC_Filter(ra_coeffs);

x__ = zeros(size(ui_data)); 
x_ = zeros(size(ui_data));
sse = [];

lim = 30;
step = 6;
count = 0;

row = 1;
for w1 = -4*lim:step:0
    col = 1;
    for w2 = 0:step:4*lim
        sum = 0;
        for n = 1:1000
            x__(n) = ls_model.new_sample(ui_data(n));
            x_(n) = ra_model.new_sample(x__(n));
            sum = (x_(n)+di_data(n)+(w1*ui_data(n))+(w2*ui_data(n+1)))^2 + sum; 
        end
        
        sse(row, col) = sum;
        col = col + 1; 
    end
    row = row + 1
end

surf(sse);
