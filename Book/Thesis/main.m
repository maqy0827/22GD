% 该文件用于处理数据，详情查看README文件

% 波长
lamuda = 652.8;

x11 = [0,2.4,3.9,6.1,7.0,10.5,12.4,13.9,14.6,17.8,19.0,19.8,21.4,23.7,25.5];
x12 = [];%未记录

x21 = [0,2.3,3.0,7.5,9.5,10.5,11.7,14.5,16.7,17.6,18.9,21.7,23.4];%正行程位移变化时电压
x22 = [0,2.0,3.4,4.4,6.4,9.7,11.5,13.5,15.2,16.4,19.2,21.5,23.4];%负行程位移变化时电压
x23 = (0:x21(1,13)/12:x21(1,13));%150V时位移5um，误差10%
y23 = 5000/150*x23;      %位移真值
y21 = lamuda/8*(0:1:12); %测量位移

x31 = [0,1.4,3.2,6.5,7.9,9.2,10.4,12.6,15.5,16.6,17.6,20.6,22.3];%正行程位移变化时电压
x32 = [0,2.2,3.6,4.6,6.5,7.9,10.8,12.2,14.3,15.7,18.7,21,22.3];%负行程位移变化时电压
x33 = 0:x31(1,13)/12:x31(1,13);
y33 = 5000/150*x33;      %位移真值
y31 = lamuda/8*(0:1:12); %测量位移

% 画第二次测量曲线
subplot(1,2,1);
hold on;
plot(x21,y21);
plot(x22,y21);
plot(x23,y23);
legend('正行程','负行程','真值');
xlabel('V(电压)');
ylabel('nm(位移)');

hold off;

% 画第三次测量曲线
subplot(1,2,2);
hold on;
plot(x31,y31);
plot(x32,y31);
plot(x33,y33);
legend('正行程','负行程','真值');
xlabel('V(电压)');
ylabel('nm(位移)');
hold off;
