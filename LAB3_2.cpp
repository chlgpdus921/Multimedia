#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void AverageFilter(InputArray _img, OutputArray _result, int n);
int main() {
	Mat img = imread("lena_noise.png", IMREAD_GRAYSCALE);
	if (img.empty())
		return -1;

	//fill with zero
	Mat result = Mat::zeros(img.size(), img.type());

	//Enter the n
	double n;
	std::cout << "Enter the n: ";
	std::cin >> n;

	AverageFilter(img, result, n);

	imshow("original image", img);
	imshow("Apply Average Filter", result);

	waitKey(0);
	return 0;
}
void AverageFilter(InputArray _img, OutputArray _result, int n) {
	Mat img = _img.getMat();
	Mat result = _result.getMat();

	double kernel = n * n, sum = 0, avg;
	int med = n / 2;
	int height = img.rows, width = img.cols;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					//Check to see if the picture pixel size is exceeded
					if (!(y + i > height - 1 || x + j > width - 1))
						sum += img.at<uchar>(y + i, x + j);
				}
			}
			avg = sum / kernel;

			//Check to see if the picture pixel size is exceeded
			if (!(y + med > height - 1 || x + med > width - 1)) {
				//If not exceeded, fill the middle value with the average value.
				result.at<uchar>(y + med, x + med) = avg;
			}
			sum = 0;
		}
	}
}
