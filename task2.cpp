#include "task2.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;
using namespace cv;

bool search(int* ary,int size, int value) {
    bool flag = false;
    for (int i = 0; i < size; i++) {
        if (ary[i] == value) {
            flag = true;
            break;
        }
    }

    return flag;
}

int main() {


    Mat img;
    img = imread("C:\\Users\\ASUS\\Downloads\\IMD063.bmp");
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

	srand(time(NULL));
	int mean1=rand()%255;
	int mean2=rand()%255;

        int i=0, i2=0, i3=0, t1=0, t2=0;


        int oldmean1=0, oldmean2=0;    //old means

        do
        {
            oldmean1 = mean1;
            oldmean2 = mean2;

            i2 = i3 = 0;
            int i = 0;
            int j1 = 0;
            int j2 = 0;
            for ( i = 0; i < row; i++)
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

   //         //printing clusters
   //         cout << endl;
   //         cout << "Cluster 1 : ";
			//cluster1.display();
   //         cout << endl;
   //         cout << "m1=" << mean1;
   //         cout << endl;
   //         cout << "Cluster 2 :";
			//cluster2.display();
   //         cout << endl;
   //         cout << "m2=" << mean2;
   //         cout << endl;
   //         cout << " ---- ";
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

                if (search(array1,size1,array[i][j]) ) {
                    img.at<Vec3b>(i, j)[0] = 0;
                    img.at<Vec3b>(i, j)[1] = 0;
                    img.at<Vec3b>(i, j)[2] = 0;

                }
                else
                {
                    img.at<Vec3b>(i, j)[0] = 255;
                    img.at<Vec3b>(i, j)[1] = 255;
                    img.at<Vec3b>(i, j)[2] = 255;
                }

            }

        imshow("Result Image", img);
        imshow("Original Image", copy);
        waitKey();

        delete[] array1;
        delete[] array2;
        //ending
		return 0;
}
