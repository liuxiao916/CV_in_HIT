%%
% author: Liu Xiao
% ID: 21S053284
% Photometric Stereo Method
clear, clc

%%
im1 = im2double(imread("im1.png"));
im2 = im2double(imread("im2.png"));
im3 = im2double(imread("im3.png"));
im4 = im2double(imread("im4.png"));

S1 = [0,0,-1];
S2 = [0,0.2,-1];
S3 = [0,-0.2,-1];
S4 = [0.2,0,-1];

%get normal
n_hat = zeros(100,100,3);
n = zeros(100,100,3);
rho = zeros(100);

S=[S1/norm(S1);S2/norm(S2);S3/norm(S3);S4/norm(S4)];

for i = 1:100
    for j = 1:100
        n_hat(i,j,:)=(inv((S'*S))*S')*[im1(i,j);im2(i,j);im3(i,j);im4(i,j)];
        rho(i,j) = norm(reshape(n_hat(i,j,:),3,1));
        n(i,j,:) = n_hat(i,j,:)/rho(i,j);
    end
end

%get depth 
z = zeros(101);
z(1) = 0;
for i = 1:100
    for j =1:100
        z(i+1,j) = z(i,j) - n(i,j,1)/n(i,j,3);
        z(i,j+1) = z(i,j) - n(i,j,2)/n(i,j,3);
    end
end

%绘制向量图
figure(1)
quiver3(z(1:100,1:100),n(:,:,1),n(:,:,2),n(:,:,3))
hold on
%绘制反射率
figure(2)
contour(rho,'Fill','on')
hold on
%绘制曲面图
[x,y] = meshgrid(1:1:101,1:1:101);
figure(3)
surf(x,y,z)
hold on


