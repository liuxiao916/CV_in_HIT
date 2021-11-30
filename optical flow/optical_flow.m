%%
% author: Liu Xiao
% ID: 21S053284
% Optical Flow
clear, clc, close

%%Main
%image1 = imread("corridor\bt.000.pgm");
%image2 = imread("corridor\bt.001.pgm");

%image1 = imread("synth\synth_000.pgm");
%image2 = imread("synth\synth_001.pgm");

%I1=im2double(image1);
%I2=im2double(image2);

image1 = imread("sphere\sphere.0.ppm");
image2 = imread("sphere\sphere.1.ppm");

I1=im2double(rgb2gray(image1));
I2=im2double(rgb2gray(image2));

H = fspecial('gaussian',[5 5],1.5);
I1 = conv2(I1,H,'same');
I2 = conv2(I2,H,'same');


WindowSzie = [21,21];    %[height, width]
[u,v] = LKoptical_flow(I1,I2,WindowSzie);
%quiver(u(end:-1:1,end:-1:1),v(end:-1:1,end:-1:1))
quiver_uv(u,v)
figure; imshow(I1); title('I1')
figure; imshow(I2); title('I2')

%%
%Function
function [u,v] = LKoptical_flow(I1,I2,windowSize)
    Tau = 0.0001; %threshold for egienvalue of AT*A

    [x2,y2] = gradient(I2);
    It = I2-I1;

    u = zeros(size(I1));
    v = zeros(size(I1));

    height = windowSize(1);
    width = windowSize(2);
    
    h = floor(height/2);
    w = floor(width/2);

    row = 1;
    for i = w+1:size(I1,1)-w
        col = 1;
        for j = h+1:size(I1,1)-h
            % Extracat window
            Ix_in_win = x2(i-w:i+w, j-h:j+h);
            Iy_in_win = y2(i-w:i+w, j-h:j+h);
            It_in_win  = It(i-w:i+w, j-h:j+h);
            Ix = Ix_in_win(:);
            Iy = Iy_in_win(:);
            b = It_in_win(:);

            %calculate
            A = [Ix Iy];

            e = eig(A'*A);
            if e(1)<Tau
                continue
            end
            flow = inv(A'*A)*A'*(-b);
            u(row,col) = flow(1);
            v(row,col) = flow(2);

            col = col+1;
        end
        row = row+1; 
    end
end

function quiver_uv(u,v)
    scalefactor = 50/size(u,2);
    u_ = scalefactor*imresize(u,scalefactor,'bilinear'); 
    v_ = scalefactor*imresize(v,scalefactor,'bilinear'); 
    quiver(u_(end:-1:1,end:-1:1),-v_(end:-1:1,end:-1:1),2); 
    axis('tight');
end
