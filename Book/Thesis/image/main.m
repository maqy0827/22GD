% 该文件用于处理数据，详情查看README文件
clc;
clear;

% 波长
lamuda = 652.8;

%记录数据
x11 = [0,2.3,3.0,6.4,8.6,9.9,11.7,14.5,16.7,17.6,18.9,21.7,23.5];%正行程位移变化时电压
x12 = [0,2.0,3.4,4.4,6.4,9.7,11.5,13.5,15.2,16.4,19.2,21.5,23.3];%负行程位移变化时电压

x21 = [0,1.4,3.2,6.5,7.9,9.2,10.4,12.6,15.5,16.6,17.6,20.6,22.3];%正行程位移变化时电压
x22 = [0,2.2,3.6,4.6,6.5,7.9,10.8,12.2,14.3,15.7,18.7,21,22.3];%负行程位移变化时电压

x31 = [0,2.1,3.1,7.1,7.6,9.8,11.0,13.5,16.0,17.1,18.3,20.9,22.5];
x32 = [0,2.0,3.4,4.6,6.5,8.8,11.2,12.8,14.8,16.0,19.0,21.3,22.5];

x = (0:x11(1,13)/12:x11(1,13));
y = lamuda/8*(0:1:12); %计算测量出的理论位移

%曲线拟合
[p1,S1] = polyfit([x11,x12,x21,x22,x31,x32],[y,y,y,y,y,y],1);
[y_fit,delta] = polyval(p1,x,S1);
corrcoef([x11,x12,x21,x22,x31,x32],[y,y,y,y,y,y])%计算相关系数并输出

set(gca, 'Fontname', 'Times newman', 'Fontsize', 12);
% 画第1次测量曲线
hold on;
plot(x11,y,'o');
plot(x12,y,'o');
plot(x21,y,'o');
plot(x22,y,'o');
plot(x31,y,'o');
plot(x32,y,'o');
plot(x,y_fit);
plot(x,y_fit+2*delta,'m--',x,y_fit-2*delta,'m--')
legend('正行程1','负行程1','正行程2','负行程2','正行程3','负行程3','拟合');
xlabel('电压(V)');
ylabel('位移(nm)');
hold off;

fprintf("标准差delta = %.2fnm\n",delta(1));

