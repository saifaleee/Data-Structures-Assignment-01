#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std; 


int Equivalence( int ** array, int search, int replace, int rows, int columns) {

	int counter = 0;
	for (int k = 0; k<rows;k++) {
		for (int l = 0; l <columns; l++) {
			if (array[k][l] == search) {
				array[k][l] = replace;
			}
			if (array[k][l] == replace) {
				counter++;
			}
		}
	}

	return counter;
}

int main()
{

	Mat img;
	img = imread("C:\\Users\\ASUS\\Downloads\\mIMD063.bmp");
	Mat copy;
	img.convertTo(copy, CV_8UC1);

	
	//allocate img_arr dynamically with img.rows and img.cols
	int** img_array = new int* [img.rows];
	for (int i = 0; i < img.rows; i++) {
		img_array[i] = new int[img.cols]{0};
	}


	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img_array[i][j] = img.at<Vec3b>(i, j)[0];
		}
	}
	const int rows = img.rows;
	const int columns = img.cols;


	int** label_array = new int* [rows];
	for (int i = 0; i < rows; i++) {
		label_array[i] = new int[columns] {};
	}

	int label = 1;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			
			if (img_array[i][j] != 0) {

				if (i == 0 && j == 0) { //upper leftmost corner point
					label_array[i][j] = label;	
					label++;
				}

				else if (i == 0 && j == rows-1)
				 { //upper rightmost corner point
					if (label_array[i][j - 1] != 0) {
						label_array[i][j] = label_array[i][j - 1];
						
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (i == columns-1 && j == 0) { //bottom leftmost corner point
					if (label_array[i-1][j] != 0) {
						label_array[i][j] = label_array[i-1][j];
					}
					else if (label_array[i - 1][j+1] != 0) {
						label_array[i][j] = label_array[i - 1][j + 1];
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (i == columns-1 && j == rows-1) { //bottom rightmost corner point
					if (label_array[i][j-1] != 0) {
						label_array[i][j] = label_array[i][j-1];
					}
					else if (label_array[i-1][j-1] != 0) {
						label_array[i][j] = label_array[i - 1][j -1];
					}
					else if (label_array[i - 1][j] != 0) {
						label_array[i][j] = label_array[i - 1][j];
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (i == 0) { //top row
					if (label_array[i][j-1] != 0) {
						label_array[i][j] = label_array[i][j - 1];
					}
					
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (i == columns-1) { //bottom row
					if (label_array[i][j - 1] != 0) {
						label_array[i][j] = label_array[i][j - 1];
					}
					else if (label_array[i - 1][j - 1] != 0) {
						label_array[i][j] = label_array[i - 1][j - 1];
					}
					else if (label_array[i - 1][j] != 0) {
						label_array[i][j] = label_array[i - 1][j];
					}
					else if (label_array[i - 1][j+1] != 0) {
						label_array[i][j] = label_array[i - 1][j+1];
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (j == 0) { // left column
					if (label_array[i-1][j] != 0) {
						label_array[i][j] = label_array[i-1][j];
					}
					else if (label_array[i - 1][j+1] != 0) {
						label_array[i][j] = label_array[i - 1][j+1];
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else if (j == rows-1) { // right column
					if (label_array[i][j -1] != 0) {
					label_array[i][j] = label_array[i][j - 1];
					}
					else if (label_array[i - 1][j-1] != 0) {
						label_array[i][j] = label_array[i - 1][j-1];
					}
					else if (label_array[i - 1][j] != 0) {
						label_array[i][j] = label_array[i - 1][j];
					}
					else {
						label_array[i][j] = label;
						label++;
					}
				}

				else {
				if (label_array[i][j - 1] != 0) {
					label_array[i][j] = label_array[i][j - 1];
				}
				else if (label_array[i - 1][j - 1] != 0) {
					label_array[i][j] = label_array[i - 1][j - 1];
				}
				else if (label_array[i - 1][j] != 0) {
					label_array[i][j] = label_array[i - 1][j];
				}
				else if (label_array[i - 1][j+1] != 0) {
					label_array[i][j] = label_array[i - 1][j+1];
				}
				else {
					label_array[i][j] = label;
					label++;
				}
				}


			}

		}
	}

	int temp=0;
	int max_label=0;
	int max_elements = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (label_array[i][j] != 0) {

				if (j != columns - 1) {
					if (label_array[i][j] != label_array[i][j + 1] && (label_array[i][j + 1] != 0)) {
						temp = Equivalence(label_array, label_array[i][j], label_array[i][j + 1],rows,columns);
						if (temp > max_elements) {
							max_elements = temp;
							max_label = label_array[i][j + 1];
						}
					}


					else if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j + 1] && (label_array[i+1][j + 1] != 0)) {
						temp = Equivalence(label_array, label_array[i][j], label_array[i + 1][j + 1],rows, columns);
						if (temp > max_elements) {
							max_elements = temp;
							max_label = label_array[i + 1][j + 1];
						}
					}
				}
				
				if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j] && (label_array[i+1][j] != 0)) {
					temp = Equivalence(label_array, label_array[i][j], label_array[i+1][j], rows, columns);
					if (temp > max_elements) {
						max_elements = temp;
						max_label = label_array[i + 1][j];
					}
				}
				else if (j != 0) {
						
					if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j - 1] && (label_array[i+1][j -1] != 0)) {
						temp = Equivalence(label_array, label_array[i][j], label_array[i + 1][j - 1], rows, columns);
						if (temp > max_elements) {
							max_elements = temp;
							max_label = label_array[i + 1][j - 1];
						}
					}

				}
				
				
			}
		}

	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (label_array[i][j] != max_label) {
				label_array[i][j] = 0;
			}
			else {
				label_array[i][j] = 255;
			}
		}
		cout << endl;
	}
	cout << max_label << " is legion region with frequency " << max_elements << endl;












































	/*
	Mat image;
	image = imread("C:\\Users\\ASUS\\Downloads\\Assignment (1)\\Assignment\\Segmented Outputs\\mIMD002.bmp");
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", image);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows(); */

	//int x;
	//for (int i = 0; i < image.rows; i++)
	//{
	//	for (int j = 0; j < image.cols; j++)
	//	{
	//		x = image.at<uchar>(i, j);
	//		//cout << x;
	//	}
	//	//cout << endl;
	//}

	//int** ptr = new int* [image.rows];
	//*ptr = new int[image.cols];
	//bool checkpixel = false;

	//for (int i = 0; i < image.rows; i++)
	//{
	//	for (int j = 0; j < image.cols; j++)
	//	{
	//		ptr[i][j] = image.at<uchar>(i, j);
	//	}
	//}

	//for (int i = 0; i < image.rows; i++)
	//{
	//	for (int j = 0; j < image.cols; j++)
	//	{
	//		if (ptr[i][j] == image.at<uchar>(i, j))
	//		{
	//			checkpixel = true;
	//		}
	//		else
	//		{
	//			checkpixel = false;
	//			break;
	//		}
	//	}

	//	if (checkpixel == false)
	//		break;

	//}



	//if (checkpixel == true)
	//{
	//	for (int i = 0; i < image.rows; i++)
	//	{
	//		for (int j = 0; j < image.cols; j++)
	//		{
	//			if (ptr[i][j] == 255)
	//				cout << "pixel is stored at row no: " << i << "col no: " << j << endl;
	//		}
	//	}

	//}

	
//Mat img;
//Mat copy;
//img.convertTo(copy, CV_8UC1);
//int** img_arr;
////allocate img_arr dynamically with img.rows and img.cols
//
//
//for (int i = 0; i < img.rows; i++)
//	for (int j = 0; j < img.cols; j++)
//		img_arr[i][j] = img.at<Vec3b>(i, j)[0];
//
//
//for (int  i = 0; i < img.rows; i++)
//	for (int j = 0; j < img.cols; j++) {
//		img.at<Vec3b>(i, j)[0] = img_arr[i][j];
//		img.at<Vec3b>(i, j)[1] = img_arr[i][j];
//		img.at<Vec3b>(i, j)[2] = img_arr[i][j];
//	}
//
//imshow("Result Image", img);
//imshow("Original Image", copy);
//waitKey();



//  

for (int i = 0; i < img.rows; i++)
	for (int j = 0; j < img.cols; j++) {
		img.at<Vec3b>(i, j)[0] = label_array[i][j];
		img.at<Vec3b>(i, j)[1] = label_array[i][j];
		img.at<Vec3b>(i, j)[2] = label_array[i][j];
	}
imshow("Result Image", img);
imshow("Original Image", copy);
waitKey();

	return 0;
}