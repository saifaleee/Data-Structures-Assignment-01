#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Header.h"

using namespace cv;
using namespace std;

int main()
{

	Mat img;
	img = imread("C:\\Users\\ASUS\\Downloads\\mIMD063.bmp");
	Mat copy;
	img.convertTo(copy, CV_8UC1);


	//allocate img_arr dynamically with img.rows and img.cols
	int** image_array = new int* [img.rows];
	for (int i = 0; i < img.rows; i++) {
		image_array[i] = new int[img.cols]{ 0 };
	}


	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			image_array[i][j] = img.at<Vec3b>(i, j)[0];
		}
	}
	const int rows = img.rows;
	const int columns = img.cols;



	LinkedList* array = new LinkedList[rows + 1.0];

	array[0].Insert(rows, 0);
	array[0].Insert(columns, 1);
	double temp=0;
	for (int i = 0, c = 1; i < rows; i++, c++) {
		int start = 0;
		temp = 0;
		for (int j = 0; j < columns; j++) {
			if (image_array[i][j] != 0) {
				array[c].Insert(j, start);
				start++;
				for (int k = j; image_array[i][k] != 0 && !(k==columns-1); k++) {
					temp = k;
				}
				if (j == columns - 1) {
					array[c].Insert((j), start);
					start++;
				}
				else {
					array[c].Insert((temp), start);
					start++;

					j = temp + 1;


				}
				
			}
		}
		array[c].Insert(-1, start);
		start++;
	}

	for (int i = 0; i < rows + 1; i++) { // print link list
		cout << i << ": ";
		array[i].display();
		cout << endl;
	}

	return 0;
}