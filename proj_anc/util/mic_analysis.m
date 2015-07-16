% opens mic data
dat = fopen('rand_30000_data.txt');
d = fscanf(dat,'%d');

% removes first N elements
N = 50;
d(1:N-1) = [];

% opens txt file of random data and scans into array x
rand = fopen('psoc_rand_30000_8b.txt');
x = fscanf(rand,'%d');

% Subtract the mean from d and x
d = d - mean(d);
x = x - mean(x);
 
dnum = numel(d);

% initialize auto-correlation R and cross-correlation P
R = zeros(N);
P = zeros(N,1);

limit = dnum-N+1;

% The number of sub-segments of length N that we can make from d,
% stepping by one, such that all samples of each sub-segment are fully contained in d
 for idx=1:limit
      xvec = x(idx:(idx+N-1));
  
      % Accumulate auto-correlation
      R = R + xvec * xvec';
    
      % Accumulate cross-correlation
      P = P + xvec * d(idx);
 end
 
% Normalize auto-correlation
R = R / limit;
    
% Normalize cross-correlation
P = P / limit;
     
% Compute impulse response to produce the least sum-of-squares
% discrepancy between x filtered by w, and d.
w = inv(R)*P;
p = stem(w);
saveas(p, 'mic_analysis.png')

% Takes output of w and saves data to text file that psoc will then read
psoc = fopen('hs_model_coeffs.h','w');

fprintf(psoc,'%s\n','#ifndef HS_MODEL_COEFFS_H');
fprintf(psoc,'%s\n','#define HS_MODEL_COEFFS_H');
fprintf(psoc,'%s\n','');
fprintf(psoc,'%s\n','static int hs_model_coeffs[]=');
fprintf(psoc,'%s\n','{');

% prints double precision values
for i=0:(N-2)
    h = 4096 * w(N-i);
    fprintf(psoc,'       %3d,\n',round(h));
end
f = 4096 * w(1);
fprintf(psoc,'       %3d\n',round(f));

fprintf(psoc,'%s\n','};');
fprintf(psoc,'%s\n','#endif');

fclose(psoc);








