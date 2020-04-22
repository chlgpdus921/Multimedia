#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;
double alpha;
int beta;
int main(int argc, char** argv) {
	string imageName("C:\\Users\\chlgp\\OneDrive\\바탕 화면\\picture.JPG");
	if (argc > 1) {
		imageName = argv[1];
	}

	std::cout << "Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "Enter the beta  value [0-100]: "; std::cin >> beta;
	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat new_image = Mat::zeros(image.size(), image.type());

	if (image.empty()) {
		cout << "Colud not open or find the image" << std::endl;
		return -1;
	}

	int height = image.rows;
	int width = image.cols;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
				}
		}
	}

	namedWindow("Original Image", 0.7);
	namedWindow("New Image",0.7);

	imshow("Original Image", image);
	imshow("New Image", new_image);
	
	waitKey(0);
	return 0;
}
