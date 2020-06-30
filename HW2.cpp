#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;
void GaussianFilter(InputArray _img, OutputArray _result, int kernel, double sigma);
int main() {
    Mat img = imread("lena_noise.png", IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    //fill with zero
    Mat result = Mat::zeros(img.size(), img.type());
    double sigma;
    int kernel = 0;
    std::cout << "Enter the kernel : "; std::cin >> kernel;
    std::cout << "Enter the sigma : "; std::cin >> sigma;

    GaussianFilter(img, result, kernel, sigma);

    namedWindow("Original Image", 1);
    imshow("Original Image", img);

    namedWindow("Result Image", 1);
    imshow("Result Image", result);

    waitKey(0);
    return 0;
}
void GaussianFilter(InputArray _img, OutputArray _result, int kernel, double sigma) {
    Mat img = _img.getMat();
    Mat result = _result.getMat();
    
    const double PI = 4.0 * atan(1.0);
    double total = 0;
    float kernalArray[50][50];
    //calculate neighour pixels
    for (int row = 0;row < kernel;row++) {
        for (int col = 0;col < kernel;col++) {
            float value = (1 / (2 * PI * pow(sigma, 2))) * exp(-(pow(row - kernel / 2, 2) + pow(col - kernel / 2, 2)) / (2 * pow(sigma, 2)));
            kernalArray[row][col] = value;
            total += value;
        }
    }
    for (int row = 0;row < kernel;row++) {
        for (int col = 0;col < kernel;col++) {
            kernalArray[row][col] = kernalArray[row][col] / total;
        }
    }

    /*Gaussian filter*/
    int rows = img.rows;
    int cols = img.cols;

    int verticleImageBound = (kernel - 1) / 2;
    int horizontalImageBound = (kernel - 1) / 2;

    for (int row = 0 + verticleImageBound;row < rows - verticleImageBound;row++) {
        for (int col = 0 + horizontalImageBound;col < cols - horizontalImageBound;col++) {
            float value = 0.0;
            for (int kRow = 0;kRow < kernel;kRow++) {
                for (int kCol = 0;kCol < kernel;kCol++) {
                    float pixel = img.at<uchar>(kRow + row - verticleImageBound, kCol + col - horizontalImageBound) * kernalArray[kRow][kCol];
                    value += pixel;
                }
            }
            result.at<uchar>(row, col) = cvRound(value);
        }
    }
}
