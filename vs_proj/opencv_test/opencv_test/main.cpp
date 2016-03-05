#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	cout << "r (default) = " << r << ";" << endl << endl;
	cout << "r (python) = " << format(r, "python") << ";" << endl << endl;
	cout << "r (numpy) = " << format(r, "numpy") << ";" << endl << endl;
	cout << "r (csv) = " << format(r, "csv") << ";" << endl << endl;
	cout << "r (c) = " << format(r, "C") << ";" << endl << endl;

	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	waitKey(0);                               // Wait for a keystroke in the window
	return 0;
}