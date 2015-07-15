% opens mic data
dat = fopen('psoc_rand_20000_8b.txt');
d = fscanf(dat,'%d');

% removes first N elements
N = 50;
d(1:N-1) = [];

% opens txt file of random data and scans into array x
rand = fopen('rand_30000_data.txt');
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