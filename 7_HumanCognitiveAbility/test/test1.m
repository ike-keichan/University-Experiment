%[test1.m]

loop = 20; %ループ回数
for i = loop: -1: 1
    switch i
        case 10
            fprintf('Ten\n');
        case 20
            fprintf('Twenty\n');
    end
end