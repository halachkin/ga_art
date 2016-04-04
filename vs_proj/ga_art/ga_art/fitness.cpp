#include "fitness.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "constants.h"

double fitness::fitness(const cv::Mat &img1, const cv::Mat &img2, FitnessMode fitness_mode)
{
	switch (fitness_mode)
	{
	default:
	case FitnessMode::MSE:
		return fitness::mean_square_err(img1, img2);
		break;
	case FitnessMode::PSNR:
		return fitness::psnr(img1, img2);
		break;
	case FitnessMode::SSIM:
		return fitness::ssim(img1, img2);
		break;
	}
}

//fitness::mean_square_err //rgb
double fitness::mean_square_err(const cv::Mat &img1, const cv::Mat &img2)
{
	cv::Mat diff;
	cv::absdiff(img1, img2, diff);
	diff.convertTo(diff, CV_32F);
	diff = diff.mul(diff);
	cv::Scalar bgr = cv::mean(diff);
	return (bgr[0] + bgr[1] + bgr[2]) / 3.0;
}

////fitnes::psnr //rgb
double fitness::psnr(const cv::Mat &img1, const cv::Mat &img2)
{
	return 10.0*log10((255 * 255) / (fitness::mean_square_err(img1, img2)));
}

//fitness::ssim //rgb
double fitness::ssim(const cv::Mat &img1, const cv::Mat &img2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	cv::Mat I1, I2;
	img1.convertTo(I1, CV_32F);
	img2.convertTo(I2, CV_32F);
	cv::Mat I2_2 = I2.mul(I2);
	cv::Mat I1_2 = I1.mul(I1);
	cv::Mat I1_I2 = I1.mul(I2);

	cv::Mat mu1, mu2;
	GaussianBlur(I1, mu1, cv::Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, cv::Size(11, 11), 1.5);
	cv::Mat mu1_2 = mu1.mul(mu1);
	cv::Mat mu2_2 = mu2.mul(mu2);
	cv::Mat mu1_mu2 = mu1.mul(mu2);
	cv::Mat sigma1_2, sigma2_2, sigma12;
	GaussianBlur(I1_2, sigma1_2, cv::Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;
	GaussianBlur(I2_2, sigma2_2, cv::Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;
	GaussianBlur(I1_I2, sigma12, cv::Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	cv::Mat t1, t2, t3;
	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);
	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);
	cv::Mat ssim_map;
	divide(t3, t1, ssim_map);
	cv::Scalar bgr = mean(ssim_map); //range -1 to 1 (1 meaning same imgs)
	return 2.0 - (1.0 + ((bgr[0] + bgr[1] + bgr[2]) / 3.0)); //range 2 to 0
}