#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include "task2.h"
#include <ctime>

//#include <conio.h>

using namespace std;
using namespace cv;

int Equivalence(int** array, int search, int replace, int rows, int columns) {

	int counter = 0;
	for (int k = 0; k < rows; k++) {
		for (int l = 0; l < columns; l++) {
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

int** task1(Mat img){

		Mat copy;
		img.convertTo(copy, CV_8UC1);


		//allocate img_arr dynamically with img.rows and img.cols
		int** img_array = new int* [img.rows];
		for (int i = 0; i < img.rows; i++) {
			img_array[i] = new int[img.cols]{ 0 };
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

					else if (i == 0 && j == rows - 1)
					{ //upper rightmost corner point
						if (label_array[i][j - 1] != 0) {
							label_array[i][j] = label_array[i][j - 1];

						}
						else {
							label_array[i][j] = label;
							label++;
						}
					}

					else if (i == columns - 1 && j == 0) { //bottom leftmost corner point
						if (label_array[i - 1][j] != 0) {
							label_array[i][j] = label_array[i - 1][j];
						}
						else if (label_array[i - 1][j + 1] != 0) {
							label_array[i][j] = label_array[i - 1][j + 1];
						}
						else {
							label_array[i][j] = label;
							label++;
						}
					}

					else if (i == columns - 1 && j == rows - 1) { //bottom rightmost corner point
						if (label_array[i][j - 1] != 0) {
							label_array[i][j] = label_array[i][j - 1];
						}
						else if (label_array[i - 1][j - 1] != 0) {
							label_array[i][j] = label_array[i - 1][j - 1];
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
						if (label_array[i][j - 1] != 0) {
							label_array[i][j] = label_array[i][j - 1];
						}

						else {
							label_array[i][j] = label;
							label++;
						}
					}

					else if (i == columns - 1) { //bottom row
						if (label_array[i][j - 1] != 0) {
							label_array[i][j] = label_array[i][j - 1];
						}
						else if (label_array[i - 1][j - 1] != 0) {
							label_array[i][j] = label_array[i - 1][j - 1];
						}
						else if (label_array[i - 1][j] != 0) {
							label_array[i][j] = label_array[i - 1][j];
						}
						else if (label_array[i - 1][j + 1] != 0) {
							label_array[i][j] = label_array[i - 1][j + 1];
						}
						else {
							label_array[i][j] = label;
							label++;
						}
					}

					else if (j == 0) { // left column
						if (label_array[i - 1][j] != 0) {
							label_array[i][j] = label_array[i - 1][j];
						}
						else if (label_array[i - 1][j + 1] != 0) {
							label_array[i][j] = label_array[i - 1][j + 1];
						}
						else {
							label_array[i][j] = label;
							label++;
						}
					}

					else if (j == rows - 1) { // right column
						if (label_array[i][j - 1] != 0) {
							label_array[i][j] = label_array[i][j - 1];
						}
						else if (label_array[i - 1][j - 1] != 0) {
							label_array[i][j] = label_array[i - 1][j - 1];
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
						else if (label_array[i - 1][j + 1] != 0) {
							label_array[i][j] = label_array[i - 1][j + 1];
						}
						else {
							label_array[i][j] = label;
							label++;
						}
					}


				}

			}
		}

		int temp = 0;
		int max_label = 0;
		int max_elements = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (label_array[i][j] != 0) {

					if (j != columns - 1) {
						if (label_array[i][j] != label_array[i][j + 1] && (label_array[i][j + 1] != 0)) {
							temp = Equivalence(label_array, label_array[i][j], label_array[i][j + 1], rows, columns);
							if (temp > max_elements) {
								max_elements = temp;
								max_label = label_array[i][j + 1];
							}
						}


						else if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j + 1] && (label_array[i + 1][j + 1] != 0)) {
							temp = Equivalence(label_array, label_array[i][j], label_array[i + 1][j + 1], rows, columns);
							if (temp > max_elements) {
								max_elements = temp;
								max_label = label_array[i + 1][j + 1];
							}
						}
					}

					if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j] && (label_array[i + 1][j] != 0)) {
						temp = Equivalence(label_array, label_array[i][j], label_array[i + 1][j], rows, columns);
						if (temp > max_elements) {
							max_elements = temp;
							max_label = label_array[i + 1][j];
						}
					}
					else if (j != 0) {

						if (i + 1 != rows && label_array[i][j] != label_array[i + 1][j - 1] && (label_array[i + 1][j - 1] != 0)) {
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
		}


		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++) {
				img.at<Vec3b>(i, j)[0] = label_array[i][j];
				img.at<Vec3b>(i, j)[1] = label_array[i][j];
				img.at<Vec3b>(i, j)[2] = label_array[i][j];
			}
		imshow("Lesion Region", img);
		return label_array;
}

bool search(int* ary, int size, int value) {
	bool flag = false;
	for (int i = 0; i < size; i++) {
		if (ary[i] == value) {
			flag = true;
			break;
		}
	}

	return flag;
}

int** task2(Mat&img) {

	Mat copy;
	img.convertTo(copy, CV_8UC1);


	const int row = img.rows;
	const int col = img.cols;
	//allocate img_arr dynamically with img.rows and img.cols
	int** array = new int* [img.rows];
	for (int i = 0; i < img.rows; i++) {
		array[i] = new int[img.cols]{ 0 };
	}


	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			array[i][j] = img.at<Vec3b>(i, j)[0];
		}
	}
	const int rows = img.rows;
	const int columns = img.cols;


	List cluster1;
	List cluster2;

	srand(time(0));
	int mean1 = rand() % 255;
	int mean2 = rand() % 255;

	int i = 0, i2 = 0, i3 = 0, t1 = 0, t2 = 0;


	int oldmean1 = 0, oldmean2 = 0;    //old means

	do
	{
		oldmean1 = mean1;
		oldmean2 = mean2;

		i2 = i3 = 0;
		int i = 0;
		int j1 = 0;
		int j2 = 0;
		for (i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++) {
				//calculating distance 
				t1 = array[i][j] - mean1;
				if (t1 < 0) { t1 = -t1; }

				t2 = array[i][j] - mean2;
				if (t2 < 0) { t2 = -t2; }

				if (t1 < t2)
				{
					//near to first mean
					cluster1.Insert(array[i][j]);
				}
				else
				{
					//near to second mean
					cluster2.Insert(array[i][j]);
				}

			}


		}
		cluster1.sizee;
		t2 = 1;
		//calculating new means
		t2 = cluster1.sum();
		mean1 = t2 / cluster1.sizee;

		t2 = 1;
		t2 = cluster2.sum();
		mean2 = t2 / cluster2.sizee;

	} while (mean1 != oldmean1 && mean2 != oldmean2); // loop will only terminate once centroids match
	cout << endl;
	cout << "Clusters created";

	/*if (mean1 > mean2) {
		cluster1.set(255);
		cluster2.set(0);
	}
	else
	{
		cluster1.set(0);
		cluster2.set(255);
	}*/

	int* array1 = cluster1.intoarray();
	int size1 = cluster1.sizee;
	int* array2 = cluster2.intoarray();
	int size2 = cluster2.sizee;

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++) {

			if (search(array1, size1, array[i][j])) {
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 0;
				img.at<Vec3b>(i, j)[2] = 0;
				array[i][j] = 0;
			}
			else
			{
				img.at<Vec3b>(i, j)[0] = 255;
				img.at<Vec3b>(i, j)[1] = 255;
				img.at<Vec3b>(i, j)[2] = 255;
				array[i][j] = 255;
			}

		}

	delete[] array1;
	delete[] array2;
	//ending
	imshow("Task2", img);
	return array;
}


int main() {

    Mat groundtruth;
    groundtruth = imread("C:\\Users\\ASUS\\Downloads\\IMD063_lesion.bmp");
	const int grows =groundtruth.rows;
	const int gcols = groundtruth.cols;

	int** ground_truth_array = new int* [grows];
	for (int i = 0; i < grows; i++) {
		ground_truth_array[i] = new int[gcols]{ 0 };
	}


	for (int i = 0; i < grows; i++) {
		for (int j = 0; j < gcols; j++) {
			ground_truth_array[i][j] = groundtruth.at<Vec3b>(i, j)[0];
		}
	}

	Mat task1_image;
	task1_image = imread("C:\\Users\\ASUS\\Downloads\\mIMD063.bmp");
	int** task1_array = task1(task1_image);

	Mat task2_image;
	task2_image = imread("C:\\Users\\ASUS\\Downloads\\IMD063.bmp");
	int** task2_array = task2(task2_image);


	double Dice_cofficient_T1=0.0;

	int TP = 0;
	int FP = 0;
	int FN = 0;

	for (int i = 0; i < task1_image.rows; i++) {
		for (int j = 0; j < task1_image.cols; j++) {
			if (task1_array[i][j] == 255 && ground_truth_array[i][j] == 255) {
				TP++;
			}
			else if (task1_array[i][j] == 255 && ground_truth_array[i][j] != 255) {
				FP++;
			}
			else if (task1_array[i][j] != 255 && ground_truth_array[i][j] == 255) {
				FN++;
			}
		}
	}


	Dice_cofficient_T1 = (2.0 * double(TP)) / (double(FN) + (2.0 * double(TP)) + double(FP));


	double Dice_cofficient_T2 = 0.0;
	TP = 0;
	FP = 0;
	FN = 0;

	for (int i = 0; i < task2_image.rows; i++) {
		for (int j = 0; j < task2_image.cols; j++) {
			if (task2_array[i][j] == 255 && ground_truth_array[i][j] == 255) {
				TP++;
			}
			else if (task2_array[i][j] == 255 && ground_truth_array[i][j] != 255) {
				FP++;
			}
			else if (task2_array[i][j] != 255 && ground_truth_array[i][j] == 255) {
				FN++;
			}
		}
	}

	Dice_cofficient_T2 = (2.0 * double(TP)) / (double(FN) + (2.0 * double(TP)) + double(FP));


	cout << "DICE Cofficient OF Task 1 : " << Dice_cofficient_T1 << endl;
	cout << "DICE Cofficient OF Task 2 : " << Dice_cofficient_T2 << endl;
	imshow("Ground Truth", groundtruth);
	waitKey();
	return 0;
}
