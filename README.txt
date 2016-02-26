Download OpenCV 2.4.11
https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.11/opencv-2.4.11.exe/download
Extract files somewhere, for example C:\OpenCV
Create env variable with opencv path
setx -m OPENCV_DIR :\OpenCV\Build\x64\vc12     (suggested for Visual Studio 2010 - 64 bit Windows)
Add to the WINDOWS PATH \bin folder (open path editor and add the following entry):
%OPENCV_DIR%\bin

Try the test opencv project \vs_proj\opencv_test - should display the image


Sources:
http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_visual_studio_Opencv/windows_visual_studio_Opencv.html#windows-visual-studio-how-to
http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html#windowssetpathandenviromentvariable

