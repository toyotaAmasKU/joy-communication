% Author : Supakit Kriangkhajorn ,2016
% Follow me : skconan

velocity = 0;
lr = 0;
f = 0;
maxscale = 100;

filename(1) = fopen('joy_forward.txt','w');
filename(2) = fopen('joy_leftright.txt','w');

while true
    [pos, btn] = mat_joy(0);
    
    if (btn(6) == 1)
        velocity = velocity + 0.5;
    else
        velocity = 0;
    end
    
    if (velocity >= maxscale)
        velocity = maxscale;
    end
    
    lr = int8(pos(1)*100);
    f = int8(velocity);
    
    fprintf('forward    : %03d\n',f);
    fprintf('left-rigth : %03d\n',lr);
    
    fprintf(filename(1),'\n%03d',f);
    fprintf(filename(2),'\n%03d',lr);
    
    pause(0.01);
end

fclose(fileID);