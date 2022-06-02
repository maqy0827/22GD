%生成论文使用图片

xlength = 10*pi;
x = 0:0.01:xlength;

y1 = (sin(x) + 1)/2;
y2 = (sin(x + pi/4) + 1)/2;

y3 = zeros(1,length(x));
y4 = zeros(1,length(x));

%begin 滞回比较器
tL = 0.4;%低阈值
tH = 0.7;%高阈值
limit = 0;%状态变量
for i = 1:length(x)
    if(limit == 0)
          y3(i) = 0.1;
    elseif(limit == 1)
           y3(i)= 0.9;
    end
    if(y1(i) <= tL)
       limit = 0; 
       y3(i) = 0.1;
    elseif(y1(i) >= tH)         
          limit = 1;  
          y3(i)= 0.9;
    end
end
%end 滞回比较器

%begin 滞回比较器
tL = 0.3;%低阈值
tH = 0.7;%高阈值
limit = 0;%状态变量
for i = 1:length(x)
    if(limit == 0)
          y4(i) = 0.1;
    elseif(limit == 1)
           y4(i)= 0.9;
    end
    if(y2(i) <= tL)
       limit = 0; 
       y4(i) = 0.1;
    elseif(y2(i) >= tH)         
          limit = 1;  
          y4(i)= 0.9;
    end
end
%end 滞回比较器

%画图
hold on;
plot(x,y1 + 4.4);
plot(x,y2 + 3.3);
plot(x,y3 + 2.2);
plot(x,y4 + 1.1);
