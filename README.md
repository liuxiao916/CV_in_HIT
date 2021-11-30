# CV_in_HIT
The homework for Computer Vision in Harbin Institute of Technology SZ

## Coordinates
本作业建立坐标系如下图  
![coordinates](data/coordinates.png)  

## Requirement
Opencv 3.4.X

## File
| File                      | Description                                                       |
| ------------------------- | ----------------------------------------------------------------- |
| calibration               | Use Opencv to calibrate a camera                                  |
| filter                    | Source code about Mean filter, Meadian filter and Gaussian filter |
| homography                | Detect chess board and calculate homography matrix                |
| optical flow              | Calculate Lucas-Knanade optical flow                              |
| Photometric Stereo Method | Use Photometric Stereo Method to rebuild a surface                |
| skin_detection            | Use color Space to detect skin in pictures                        |


## Result
### Calibration
![calibration](data/calibration.png)
### Filter
![Gaussian](data/filter/dst/Gausian55_opencv.jpg)

### Homography
<p float="left">
    <img src="homography/result/left7/dst.jpg" width="300"/><img src="homography/result/left7/left7.png" width="300"/>
</p>

### Optical Flow
<center float="left">
    <img src="optical flow\sphere0.png" width="300"/><img src="optical flow\dst.jpg" width="300"/>
</center>

### Photometric Stereo Method
![PSM](Photometric%20Stereo%20Method/重建图.jpg)

### Skin Detection
<center class="half">
    <img src="data\skin\picture1.png" width="300"/><img src="data\skin\dst1.png" width="300"/>
</center>


