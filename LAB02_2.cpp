#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int beta;
int main(int argc, char** argv) {
	double alpha = 0.5; 
	double beta, input;


	std::cout << "Simple Linear Blender " << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << "* Enter alpha [0-1]: ";
	std::cin >> input;

	if (input >= 0.0 && input <= 1.0)
		alpha = input;

	Mat src1 = imread("img.jpg");
	Mat src2= imread("img2.jpg");
	
	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}
	if (!src2.data) {
		printf("Error loading src2 \n");
		return -1;
	}
	resize(src1, src1, cv::Size(src2.rows, src2.cols), 0, 0, INTER_NEAREST);
	namedWindow("Linear Blend", 0.2);
	beta = (1.0 - alpha);

	Mat dst = Mat::zeros(src1.size(), src1.type());

	for (int y = 0; y < src1.rows; y++) {
		for (int x = 0; x < src1.cols; x++) {
			for (int c = 0; c < 3; c++) {
				dst.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * (src1.at < Vec3b>)(y, x)[c]) + beta + src2.at<Vec3b>(y, x)[c];
			}
		}
	}

	imshow("Linear Blend", dst);

	waitKey(0);
	return 0;

}
