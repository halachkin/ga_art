# Genetic Art project


Just another [EvoLisa](https://rogeralsing.com/2008/12/16/evolisa-optimizations-and-improved-quality/) clone 

Authors: Aliaksei Halachnkin, Denis Fedor


## Info
Currently running hill climbing algorithm with some modifications, 
logs are [here](https://www.dropbox.com/sh/l9wz9c40l0ojlkb/AAAH5JHAYtKVX-7JrNMoQAc2a?dl=0)

[**OUR OPENCV BUILD (Visual Studio 2015 - 64 bit)**]( https://www.dropbox.com/sh/g2ldbzlngww10jd/AABAwlcqHEtOkLhhlQhJQ39Ka?dl=0)

## OpenCV installing

+ **USING PREBUILDED BINARIES** 
    1. Download [OpenCV 2.4.11](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.11/opencv-2.4.11.exe/download)
    2. Extract files somewhere, for example C:\OpenCV
    2. Create env variable with opencv path
setx -m OPENCV_DIR C:\OpenCV\Build\x64\vc12     (suggested for Visual Studio 2010 - 64 bit Windows)
Add to the WINDOWS PATH \bin folder (open path editor and add the following entry):
%OPENCV_DIR%\bin
    3. Try the test opencv project \vs_proj\opencv_test - should display the image
+ **BUILD OPENCV**
 
    1. Download [OpenCV 2.4.11](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.11/opencv-2.4.11.exe/download)
    2. Extract files somewhere, for example C:\OpenCV
    3. Install cmake http://www.cmake.org/cmake/resources/software.html
    4. Create folder for the build, for example C:\OpenCV\mybuild
    5. Generate Visual Studio solution using cmake
    6. Open generated solution and build solution in debug and release mode
    7. Build CMakeTargets INSTALL in debug and release mode (bin and lib folders went into C:\OpenCV\opencv\mybuild\install)
    /. set env variable with opencv path:
    setx -m OPENCV_DIR C:\OpenCV\opencv\mybuild\install
    Add to the WINDOWS PATH \bin folder (open path editor and add the following entry):
    %OPENCV_DIR%\bin

    8. Try the test opencv project \vs_proj\opencv_test - should display the image and
      display matrix
    



+ Sources:
    1. http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_visual_studio_Opencv/windows_visual_studio_Opencv.html#windows-visual-studio-how-to
    2. http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html#windowssetpathandenviromentvariable
    3. http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html
    4. http://inside.mines.edu/~whoff/courses/EENG510/lectures/other/CompilingOpenCV.pdf
