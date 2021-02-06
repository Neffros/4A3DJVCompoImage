# Visual studio settings

## Character set
Since the directory reading uses TCHAR and we convert them to string, we need to use multi-byte characters.
You can configure that in the project settings as shown in the image below:

[settings1](/readmeImages/settings1.PNG)

## Filesystem
Since we are using filesystem, we need to use c++ 17.
You can configure that in the project settings as shown in the image below:

[settings2](/readmeImages/settings2.PNG)

## OpenCV installation

To read video format we are using openCV. Please, install it by following instruction at this [link](https://www.opencv-srf.com/2017/11/install-opencv-with-visual-studio.html)
Go to the folder opencv\build\x64\vc15\bin to take opencv_world451.dll (or other version) and put it in your project at path D:\Dev\traitement_image\4A3DJVCompoImage\x64\Release.
Otherwise you couldn't launch in release mode who is faster.
## Menu 

Please launch this programme in release mode to be faster. You can navigate through a menu to apply settings and choose images or video directory.
Simply following instruction in console.

