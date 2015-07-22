clear all
close all

order = 1000;
lambda = 0.999;

ui_filename = '5 symphony 15 sec.wav';
[ui_data,ui_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', ui_filename));  % reading .wav file as undesired sound
ui_data = ui_data(:,1);

n_samps = min(20000,numel(ui_data));  

for log_ord=1:12

    order = round(2^log_ord);
    
    P = eye(order);
    R = 0.0 * eye(order);
    Rfull = 0.0 * eye(order);
    
    pause on
    
    
    for n=1:n_samps
    
        x=ui_data(n:n+order-1);
        
        Rfull = Rfull + x * x';

        if (mod(n,10000) == 0)
            fprintf('.');
        end
    end

    fprintf( '\n\norder=%d, cond(R)=%5.2g\n', order, cond(Rfull) )

end



% Results:
%% 
%% 
%% order=2, cond(R)=3.3e+02
%% order=4, cond(R)=7.6e+04
%% order=8, cond(R)=1.2e+07
%% order=16, cond(R)=1.9e+09
%% order=32, cond(R)=3.1e+09
%% order=64, cond(R)=4.5e+09
%% order=128, cond(R)=5.2e+09
%% order=256, cond(R)=7.2e+09
%% order=512, cond(R)=1.1e+10
%% order=1024, cond(R)=1.9e+10
%% order=2048, cond(R)=5.5e+10
%% order=4096, cond(R)=1.7e+11
