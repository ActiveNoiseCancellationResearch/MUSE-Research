function dummy = room_acoustics_to_coeffs(Qi, ri, ui_fs)
T = 1/ui_fs;                                   % sampling period
c = 345;                                       % speed of sound at 20 degrees Celsius
if isequal((numel(Qi)),(numel(ri)))
    di = ri/c;                                 % d is delays in seconds
    ni = round(di/T);                          % discrete time index corresponding to the ith reflection
    max_ni = max(ni);                          % define maximum source distance
    dummy = zeros(1,(max_ni+2));               % init storage             
    for i = 1:numel(Qi)
        dummy(ni(i))= Qi(i)/ri(i);             % fill in non-zero values
    end
else
    disp('Error: Size of source distance array is not the same length as image source strength array');
    
end
end

