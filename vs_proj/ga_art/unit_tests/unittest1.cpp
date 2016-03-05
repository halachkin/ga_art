#include "stdafx.h"
#include "CppUnitTest.h"



#include "..\ga_art\fitness.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace unit_tests
{		
	TEST_CLASS(TEST_FITNESS)
	{
	public:
		
		TEST_METHOD(test_fitness_1)
		{
			cv::Mat img1 = cv::Mat::zeros(1, 1, CV_8UC3);
			cv::Mat img2 = cv::Mat::zeros(1, 1, CV_8UC3);
			img1.at<cv::Vec3b>(0, 0)[0] = 1;
			img1.at<cv::Vec3b>(0, 0)[1] = 2;
			img1.at<cv::Vec3b>(0, 0)[2] = 3;

			img2.at<cv::Vec3b>(0, 0)[0] = 3;
			img2.at<cv::Vec3b>(0, 0)[1] = 2;
			img2.at<cv::Vec3b>(0, 0)[2] = 1;

			double result = fitness::mean_square_err(img1, img2);
			double expected = 8 / 3.0;
			Assert::AreEqual(expected, result);

		}

	};
}