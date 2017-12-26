#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;


int findthreshold(int intensityfrequency[], int threshold, int newthreshold)
{
	if (newthreshold == threshold)
	{
		return threshold;
	}
	else
	{

		float darkcluster = 0;
		float lightcluster = 0;
		float darkclustermean = 0, lightclustermean = 0;
		for (int p = 0; p < threshold; p++)
		{
			darkcluster = darkcluster + intensityfrequency[p];
		}

		for (int q = int(threshold + 1); q <= 255; q++)
		{
			lightcluster = lightcluster + intensityfrequency[q];

		}

		float darkclustersum = 0, lightclustersum = 0;
		for (int p = 0; p < threshold; p++)
		{
			darkclustersum += p*intensityfrequency[p];
		}
		darkclustermean = darkclustersum / darkcluster;

		for (int q = int(threshold + 1); q <= 255; q++)
		{
			lightclustersum += q * intensityfrequency[q];

		}
		lightclustermean = lightclustersum / lightcluster;

		newthreshold = (darkclustermean + lightclustermean) / 2;


		if (newthreshold == threshold)
		{
			return threshold;
		}

		else
		{
			threshold = newthreshold;
			newthreshold = 0;
		}

		return findthreshold(intensityfrequency, threshold, newthreshold);

	}


}
//Function for printing images
void printimage(string windowname, Mat image) {

	namedWindow(windowname, CV_WINDOW_AUTOSIZE);
	imshow(windowname, image);
	//waitKey(0);
}
//Fucntion for Minimum element of array for using in Erosion
int minimum(int arr[]) {
	int minimum = 255;
	for (int i = 0; i < sizeof(arr); i++) {
		if (arr[i] < minimum) {
			minimum = arr[i];
		}
	}
	return minimum;
}
//Fucntion for Maximum element of array for using in Dilation
int maximum(int arr[]) {
	int maximum = 0;
	for (int i = 0; i < sizeof(arr); i++) {
		if (arr[i] > maximum) {
			maximum = arr[i];
		}
	}
	return maximum;
}
// 11*11 Erosion Function
Mat Erosion(Mat binaryMat, int mask[11][11]) {
	cv::Mat erosionMat(binaryMat.size(), binaryMat.type());
	for (int i = 0; i < binaryMat.rows; i++) {
		for (int j = 0; j < binaryMat.cols; j++) {
			erosionMat.at<uchar>(i, j) = 0;
		}
	}


	for (int i = 2; i < binaryMat.rows - 2; i++) {
		for (int j = 2; j < binaryMat.cols - 2; j++) {
			int currentpixelvalue = 255;
			int count = 0;
			int setflag = 0;
			for (int a = -2; a <= 2; a++) {

				for (int b = -2; b <= 2; b++) {

					if (mask[a + 2][b + 2] == binaryMat.at<uchar>(i + a, j + b)) {

					}
					else { setflag = 1; }

				}

			}
			if (setflag == 0)
				erosionMat.at<uchar>(i, j) = currentpixelvalue;

		}

	}

	return erosionMat;
}
//3*3 Erosion Function
Mat Erosion_small(Mat binaryMat, int mask[3][3]) {
	cv::Mat erosionMat(binaryMat.size(), binaryMat.type());
	for (int i = 0; i < binaryMat.rows; i++) {
		for (int j = 0; j < binaryMat.cols; j++) {
			erosionMat.at<uchar>(i, j) = 0;
		}
	}


	for (int i = 2; i < binaryMat.rows - 2; i++) {
		for (int j = 2; j < binaryMat.cols - 2; j++) {
			int currentpixelvalue = 255;
			int count = 0;
			int setflag = 0;
			for (int a = -2; a <= 2; a++) {

				for (int b = -2; b <= 2; b++) {

					if (mask[a + 2][b + 2] == binaryMat.at<uchar>(i + a, j + b)) {

					}
					else { setflag = 1; }

				}

			}
			if (setflag == 0)
				erosionMat.at<uchar>(i, j) = currentpixelvalue;

		}

	}

	return erosionMat;
}
//3*3 Dilation Function
Mat Dilation_small(Mat binaryMat, int mask[3][3]) {
	cv::Mat dilatedMat(binaryMat.size(), binaryMat.type());
	for (int i = 0; i < binaryMat.rows; i++) {
		for (int j = 0; j < binaryMat.cols; j++) {
			dilatedMat.at<uchar>(i, j) = 0;
		}
	}


	for (int i = 2; i < binaryMat.rows - 2; i++) {
		for (int j = 2; j < binaryMat.cols - 2; j++) {
			int currentpixelvalue = 255;
			int count = 0;
			int setflag = 1;
			for (int a = -2; a <= 2; a++) {


				for (int b = -2; b <= 2; b++) {

					if (mask[a + 2][b + 2] == binaryMat.at<uchar>(i + a, j + b)) {
						setflag = 0;
					}

				}

			}
			if (setflag == 0)
				dilatedMat.at<uchar>(i, j) = currentpixelvalue;

		}

	}
	return dilatedMat;
}
// 11*11 Dilation Function
Mat Dilation(Mat binaryMat, int mask[11][11]) {
	cv::Mat dilatedMat(binaryMat.size(), binaryMat.type());
	for (int i = 0; i < binaryMat.rows; i++) {
		for (int j = 0; j < binaryMat.cols; j++) {
			dilatedMat.at<uchar>(i, j) = 0;
		}
	}


	for (int i = 2; i < binaryMat.rows - 2; i++) {
		for (int j = 2; j < binaryMat.cols - 2; j++) {
			int currentpixelvalue = 255;
			int count = 0;
			int setflag = 1;
			for (int a = -2; a <= 2; a++) {


				for (int b = -2; b <= 2; b++) {

					if (mask[a + 2][b + 2] == binaryMat.at<uchar>(i + a, j + b)) {
						setflag = 0;
					}

				}

			}
			if (setflag == 0)
				dilatedMat.at<uchar>(i, j) = currentpixelvalue;

		}

	}
	return dilatedMat;
}

// Function for performing Erosion on gray scale image
Mat GrayScaleEroison(Mat greyimage) {
	int o = 3;
	int mask[3][3];
	for (int a = 0; a < o; a++) {
		for (int b = 0; b < o; b++) {
			mask[a][b] = 1;
		}
	}
	int arr[10];

	cv::Mat erodedimage(greyimage.size(), greyimage.type());
	//printimage("Original Image Eroded", erodedimage);
	for (int i = 1; i < greyimage.rows - 1; i++) {
		for (int j = 1; j < greyimage.cols - 1; j++) {
			int value = 0, count = 0;
			for (int a = -1; a <= 1; a++) {
				for (int b = -1; b <= 1; b++) {
					arr[count] = greyimage.at<uchar>(i + a, j + b)*mask[a + 1][b + 1];
					count++;
				}
			}
			erodedimage.at<uchar>(i, j) = minimum(arr);
		}
	}

	printimage("Original Image Eroded", erodedimage);
	return greyimage;
}

// Function for performing Dilation on gray scale image
Mat GrayScaleDilation(Mat greyimage) {

	int o = 3;
	int mask[3][3];
	for (int a = 0; a < o; a++) {
		for (int b = 0; b < o; b++) {
			mask[a][b] = 1;
		}
	}
	int arr[10];

	cv::Mat dilatedimage(greyimage.size(), greyimage.type());
	//printimage("Original Image Eroded", dilatedimage);
	
	//printimage("Original Image Eroded", dilatedimage);
	for (int i = 1; i < greyimage.rows - 2; i++) {
		for (int j = 1; j < greyimage.cols - 2; j++) {
			int value = 0, count = 0;
			for (int a = -1; a <= 1; a++) {
				for (int b = -1; b <= 1; b++) {
					arr[count] = greyimage.at<uchar>(i + a, j + b)*mask[a + 1][b + 1];
					count++;
				}
			}
			dilatedimage.at<uchar>(i, j) = maximum(arr);
		}
	}

	printimage("Original Image Dilated", dilatedimage);
	return greyimage;
}

int main()
{
	std::ofstream ofs1, ofs2;
	ofs1.open("test.txt", std::ofstream::out | std::ofstream::app);
	ofs2.open("testfreqimg.txt", std::ofstream::out | std::ofstream::app);
	int n = 0;
	int m = 11;
	int o = 3;
	//int mask[5][5] = { {255,255,255,255,255},{255,255,255,255,255 },{255,255,255,255,255 },{ 255,255,255,255,255 },{ 255,255,255,255,255 } };
	// generating masks dynamically of a particular range
	int mask[11][11];
	for (int a = 0; a < m; a++) {
		for (int b = 0; b < m; b++) {
			mask[a][b] = 255;
		}
	}

	int mask2[3][3];
	for (int a = 0; a < o; a++) {
		for (int b = 0; b < o; b++) {
			mask2[a][b] = 255;
		}
	}

	Mat image;

	// LOAD image
	image = imread("Test_image.bmp", CV_LOAD_IMAGE_GRAYSCALE


	);
	

	cv::Mat binaryMat(image.size(), image.type());
	cv::Mat FinalMat(image.size(), image.type());
	cv::Mat binaryMat2(image.size(), image.type());
	cv::Mat erosionMat(image.size(), image.type());
	cv::Mat dilatedMat(image.size(), image.type());
	cv::Mat erodedMat(image.size(), image.type());

	//Apply thresholding

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			ofs1 << i << " " << j << " " << int(image.at<uchar>(i, j)) << "\n";
		}
	}

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (image.at<uchar>(i, j) < 170) {
				binaryMat2.at<uchar>(i, j) = 0;
			}
			else binaryMat2.at<uchar>(i, j) = 255;
		}
	}
	
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", image);
	waitKey(0);
	printimage("Binary Image", binaryMat2);
	waitKey(0);

	GrayScaleEroison(image);

	GrayScaleDilation(image);
	waitKey(0);
	binaryMat = Erosion(binaryMat2, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	
	binaryMat = Erosion(binaryMat, mask);
	
	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation_small(binaryMat, mask2);
	

	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	binaryMat = Erosion(binaryMat, mask);
	

	binaryMat = Dilation_small(binaryMat, mask2);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);
	binaryMat = Dilation(binaryMat, mask);


	FinalMat = binaryMat.clone();
	printimage("Final Image", FinalMat);
	waitKey(0);
	
	return 0;
}