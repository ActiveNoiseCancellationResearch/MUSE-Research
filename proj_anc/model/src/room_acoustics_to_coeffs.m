function ra_coeffs = room_acoustics_to_coeffs(Qi, ri, ui_fs)
T = 1/ui_fs;                                   % sampling period
c = 345;                                       % speed of sound at 20 degrees Celsius
if isequal((size(Qi)),(size(ri)))
    di = ri/c;                                 % d is delays in seconds
    ni = round(di/T);                          % discrete time index corresponding to the ith reflection
    max_ni = max(ni);                          % define maximum source distance
    ra_coeffs = zeros(1,((max_ni)+2));         % init storage
    for i = 1:size(Qi)
        ra_coeffs(ni(i))= Qi(i)/ri(i);         % fill in non-zero values
    end
else
    disp('Error: Size of source distance array is not the same length as image source strength array');
    
end
end

