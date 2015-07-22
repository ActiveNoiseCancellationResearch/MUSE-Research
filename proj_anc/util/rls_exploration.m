clear all
close all

order = 1000;
lambda = 0.999;

ui_filename = '5 symphony 15 sec.wav';
[ui_data,ui_fs] = audioread(strcat(getenv('PROJ_ANC'), '\model\stimulus\', ui_filename));  % reading .wav file as undesired sound
ui_data = ui_data(:,1);

n_samps = min(660000,numel(ui_data));  

P = eye(order);
R = 0.0 * eye(order);
Rfull = 0.0 * eye(order);

pause on

for n=1:n_samps

    x=ui_data(n:n+order-1);
    
    R = lambda * R + x * x';
    Rfull = Rfull + x * x';
    
    g = (P * x)/(lambda + x' * P * x);
    
    P = (P - g * x' * P)/lambda;
    
    if (mod(n, 1000) == 0)
        i = round(n/1000);
        condn(i,1:3) = [cond(P), cond(R), cond(Rfull)];
        sprintf( '%8d: cond P=%5.0f, R=%5.0f, Rfull=%5.0f', n, condn(i,1), condn(i,2), condn(i,3) )
    end
end
