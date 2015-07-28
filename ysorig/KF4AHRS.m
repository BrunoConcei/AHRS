%kalman filter simu for AHRS

clear;
close all;
%% preproccess
%load data
data = textread('LOG140308_2210.txt');
data = data(5100:end,:);
gyr = data(:,1:3);
acc = data(:,4:6);
mag = data(:,7:9);

%% set parameters
sampleNum=19000;    %�����趨�����ܲ���������С�����ݵ�����
dt=0.005;            %�������ڣ���ʵ�����һ�£�����Ĳ�����Ϊ200Hz

%filter parameters

%for UKF
P=diag([0.007 0.007 0.007 0.007 0.1 0.1 0.1])^2;    %�������Э������
Q=diag([0.002 0.002 0.002 0.002 0.0005 0.0005 0.0005])^2;   %��������Э������
R=diag([0.1 0.1 0.1 0.2 0.2 0.2])^2; %�۲�����Э������

%for EKF
% P=diag([0.7 0.7 0.7 0.7 1.1])^2;
% Q=diag([0.04 0.01 0.01 0.04 0.1])^2;
% R=diag([1.6 1.6 1.2 0.002 0.002 0.005 0.7])^2;

%% alignment
alignNum = 200:400;      %��ǰ�洦�ھ�ֹ״̬��1000�����������г�ʼ��
x=zeros(7,1);           %״̬������5ά��������̬��Ԫ������ת������

av_acc=data(alignNum,4:6);
av_acc = mean(av_acc);  %ǰ��1000�����ݵľ�ֵ
gnorm = norm(av_acc);   %�������ٶȵ�ģ�����ڽ����ٶȼƵĵ�λ����Ϊg
av_acc = av_acc/gnorm;
roll = atan2(-av_acc(2),-av_acc(3));    %��ʼ�����
pitch = asin(av_acc(1));                %��ʼ������

av_mag=data(alignNum,7:9);
av_mag = mean(av_mag);  %ǰ��1000���ͨ�����ݵľ�ֵ
mnorm = norm(av_mag);   %�ش�ʸ����ģ
av_mag = av_mag/mnorm;

%��֪��ת�ǡ������ǣ���������ϵ�ڵ�����ʸ�����ش�ʸ������������ϵ�ڵ�����ʸ�����ش�ʸ������ƫ����
Hx=[cos(pitch),sin(pitch)*sin(roll),cos(roll)*sin(pitch)]*av_mag';
Hy=[0,cos(roll),-sin(roll)]*av_mag';

if(Hy<0.001 & Hy>-0.001)
    if Hx>0
        yaw=0;
    else
        yaw=pi;
    end
else
    if Hy<0
        yaw=atan(Hx/Hy)+pi/2;
    else
        yaw=atan(Hx/Hy)+3*pi/2;
    end
end

% yaw=yaw-(6+37/60)/180*pi;
if yaw<0
    yaw=yaw+2*pi;
end

%������õ�ŷ���ǣ������ʼ��Ԫ��
x(1:4) = myAngle2Quat([roll pitch yaw]);
x(5:7) = [1;1;1];
Cbn = myQuat2Cbn(x(1:4));
%% estimate geomagn
m0=myAngle2Cbn([roll pitch yaw])*av_mag'; 

%% kalman processing
%record interesting data
%���ڼ�¼���ݵı���
xRec = zeros(7,sampleNum);

%������ϵͳ����
afunc = @INS_update;
%�����Թ۲ⷽ��
hfunc = @GetEstiOb;
%����ϵͳ�ſ˱Ⱦ���ĺ���
geta = @GetA;
%����۲ⷽ���ſ˱Ⱦ���ĺ���
geth = @GetH;

%����ʹ����matlab ekf_ukf�㷨�������õ���UKF����
for i=1:sampleNum

    %Ԥ�����
%     [x, P, D] = ukf_predict1(x, P, afunc, Q, dt);%[M,P,D] = ukf_predict1(M,P,f,Q,f_param,alpha,beta,kappa,mat)
    [x, P] = ekf_predict1(x,P,geta,Q,afunc,eye(length(x)),[gyr(i,:) dt]);
%    x = INS_update(x,dt);
%    A = GetA(x,dt);
%    P = A*P*A'+Q;
    
   %extract measure from raw_data---------------------------------
   %��ȡ�۲���
   z = zeros(6,1);
   z(1) = acc(i,1);    %g component along x axis
   z(2) = acc(i,2);    %g component along y axis
   z(3) = acc(i,3);    %g component along z axis
   
   z(4) = mag(i,1);  %geomagn along x axis
   z(5) = mag(i,2);  %y
   z(6) = mag(i,3);  %z
   
   %��λ����
   z(1:3) = z(1:3)/gnorm;    %normalize
   z(4:6) = z(4:6)/mnorm;    %normalize   

%     hx = GetEstiOb(x,m0);
    %update
    if abs(z(1))<1 && abs(z(2))<1 %�����ٶȼ����������趨��ֵ���򱾴β��ں�
%      [x, P, K, Mu, S, LH] = ukf_update1(x, P, z, hfunc, R, m0);     %
    [x, P, K, MU, S, LH] = ekf_update1(x,P,z,geth,R,hfunc,eye(length(z)),m0);
%        H = GetH(x,m0);
%        K = P*H'*(H*P*H'+R)^-1;  
% 
%        %residual error
%        resiErr = z-hx;
%        x = x+K*resiErr;
%        P = (eye(5)-K*H)*P;
    end
   
   %normalize quaternion
   x(1:4) = x(1:4)/norm(x(1:4));    %��Ԫ����һ��
   xRec(:,i) = x;   %��¼����
end

%%
angle=zeros(3,sampleNum);
for i=1:sampleNum
    [angle(3,i) angle(2,i) angle(1,i)]=quat2angle(xRec(1:4,i)');
end

figure;
plot(angle(1,:)*57.3);
hold on;
plot(angle(2,:)*57.3,'r');

%% ���������̬��Ԫ������
figure;
plot(xRec(1,:));
hold on;
plot(xRec(2,:),'r');
plot(xRec(3,:),'g');
plot(xRec(4,:),'y');
grid on;
title('quaternion');
%%
figure;
plot(xRec(5,:));
hold on;
plot(xRec(6,:),'r');
plot(xRec(7,:),'g');
grid on;
title('scale');