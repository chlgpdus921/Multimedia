#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>
#include <iostream>
using namespace cv;
using namespace std;
int main() {
	double scale_row, scale_col;

	cout << "Enter the row : ";
	cin >> scale_row;
	cout << "Enter the col : ";
	cin >> scale_col;

	Mat input = imread("angry.jpg", IMREAD_COLOR);
	Mat output = Mat::zeros(input.rows * scale_row, input.cols * scale_col, input.type());

	Mat resizeImage;
	resize(input, resizeImage, Size(), scale_col, scale_row, INTER_LINEAR);

	for (int y = 0; y < output.rows; y++) {
		for (int x = 0; x < output.cols; x++) {
			int i = int(x / scale_col);
			int j = int(y / scale_row);

			double x1 = (double)x / (double)scale_col - (double)i;
			double x2 = 1 - x1;
			double y1 = (double)y / (double)scale_row - (double)j;
			double y2 = 1 - y1;

			double w1 = x2 * y2;
			double w2 = x1 * y2;
			double w3 = x2 * y1;
			double w4 = x1 * y1;

			if (i == input.cols - 1)
				i--;
			if (j == input.rows - 1)
				j--;


			Vec3b p1 = input.at<Vec3b>(j, i);
			Vec3b p2 = input.at<Vec3b>(j, i + 1);
			Vec3b p3 = input.at<Vec3b>(j + 1, i);
			Vec3b p4 = input.at<Vec3b>(j + 1, i + 1);

			output.at<Vec3b>(y, x) = w1 * p1 + w2 * p2 + w3 * p3 + w4 * p4;

		}
	}

	namedWindow("Original Image");
	imshow("Original Image", input);

	namedWindow("Compare Image");
	imshow("Compare Image", resizeImage);

	namedWindow("Result Image");
	imshow("Result Image", output);

	waitKey(0);

	return 0;
}
