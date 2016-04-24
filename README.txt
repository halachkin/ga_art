Genetic Art project

\bin\ga_art.exe IMAGE_PATH CONFIG_PATH

Info
    Currently running hill climb algorithm with some modifications
    logs are here (about 600 Mb too many images) 
    https://www.dropbox.com/sh/nm8l5a28uwugsck/AAAP_7tMrSX_VQ9WJUZ_8ZsUa?dl=0
    See some of statistics at vs_proj\ga_art\ga_art\logs\DEEP_ANALYTICS.HTML


OpenCV installing
    +USING PREBUILDED BINARIES 

        Download OpenCV 2.4.11
        https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.11/opencv-2.4.11.exe/download
        Extract files somewhere, for example C:\OpenCV

        Create env variable with opencv path
        setx -m OPENCV_DIR C:\OpenCV\Build\x64\vc12     (suggested for Visual Studio 2010 - 64 bit Windows)
        Add to the WINDOWS PATH \bin folder (open path editor and add the following entry):
        %OPENCV_DIR%\bin

        Try the test opencv project \vs_proj\opencv_test - should display the image

    +BUILD OPENCV

        Download OpenCV 2.4.11
        https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.11/opencv-2.4.11.exe/download
        Extract files somewhere, for example C:\OpenCV

        Install cmake http://www.cmake.org/cmake/resources/software.html
        Create folder for the build, for example C:\OpenCV\mybuild
        Generate Visual Studio solution using cmake
        Open generated solution and build solution in debug and release mode
        Build CMakeTargets INSTALL in debug and release mode
        bin and lib folders went into C:\OpenCV\opencv\mybuild\install
        set env variable with opencv path:
        setx -m OPENCV_DIR C:\OpenCV\opencv\mybuild\install
        Add to the WINDOWS PATH \bin folder (open path editor and add the following entry):
        %OPENCV_DIR%\bin

        Try the test opencv project \vs_proj\opencv_test - should display the image and
        display matrix

    +OUR OPENCV BUILD (Visual Studio 2015 - 64 bit)
        https://www.dropbox.com/sh/g2ldbzlngww10jd/AABAwlcqHEtOkLhhlQhJQ39Ka?dl=0

    Sources:
    http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_visual_studio_Opencv/windows_visual_studio_Opencv.html#windows-visual-studio-how-to
    http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html#windowssetpathandenviromentvariable


    http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html
    http://inside.mines.edu/~whoff/courses/EENG510/lectures/other/CompilingOpenCV.pdf