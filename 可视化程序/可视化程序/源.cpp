
#include "cv.h"

#include "highgui.h"

#include <cstdio>



//read the img data from the Memory to own array

void ReadImageData(unsigned char *src, int rows, int cols, int width_step, unsigned char ** &dst)

{

	int count = 0;

	for (int i = 0; i < cols; ++i)

	{

		for (int j = 0; j < rows; ++j)

		{

			// printf("%c\n", *((unsigned char*)dst + rows * i + j));

			// *((unsigned char*)dst + rows * i + j) = src[count];

			dst[i][j] = src[count];

			count++;

		}

	}

	printf("%d\n", count);

	return;

}

//���û��Լ�����洢�����뿽����ͼ����Ӧ���ڴ�λ��

//write the img data ( my array) to the memory

void WriteImageData(unsigned char *src, int rows, int cols, int width_step, unsigned char ** &dst, bool flag)

{

	int count = 0;

	for (int i = 0; i < cols; ++i)

	{

		for (int j = 0; j < rows; ++j)

		{

			if (flag) src[count] = dst[i][j];

			else src[count] = (unsigned char)'a';

			count++;

		}

	}

	printf("%d\n", count);



	return;

}



int main(int args, char * argv[])

{

	//	double PI = 0.0;

		//�趨ͼƬ�Ĵ�С

	int width = 500;

	int height = 500;

	//����opencv����һ�� �յ�ͼƬͼ��

	IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	unsigned char *img_data = (unsigned char *)(img->imageData);

	//��� һ�� ��С

	int width_step = img->widthStep;



	//��̬���� �����ε� ��ά����  �߳�Ϊwidth

	unsigned char **array_of_img;

	array_of_img = new unsigned char *[width_step];

	array_of_img[0] = new unsigned char[width_step * width_step];



	//Ϊÿһ�� �����ַ

	for (int i = 1; i < width_step; ++i)

	{

		array_of_img[i] = array_of_img[i - 1] + width_step;

	}

	//��ʼ����̬ �����Ķ�ά���� 0������ɫ

	for (int k = 0; k < width_step; ++k)

	{

		for (int j = 0; j < width_step; ++j)

		{

			array_of_img[k][j] = 0;

		}

	}

	//�����������д�뵽�ڴ���Ӧ��λ��

	WriteImageData(img_data, width_step, width_step, width_step, array_of_img, true);

	//��Բ

	cvCircle(img, cvPoint(250, 250), 250, cvScalar(255), 1, 8, 0);



	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);//��������

	cvShowImage("Image", img);//��ʾͼ��

	cvWaitKey(0); //�ȴ���������ʼ���������



	int sumSquare = 10000;

	int sumCircle = 0;



	double PI = 0.0;

	//generate 100 point(x,y)

	for (int count = 0; count < sumSquare; ++count)

	{

		//���������з���Ԫ�ص�ֵ��5 ʹ��ɫ�䰵

		for (int n = 0; n < width_step; ++n)

		{

			for (int m = 0; m < width_step; ++m)

			{

				if (array_of_img[m][n] > 0)

				{

					array_of_img[m][n] -= 5;

				}

			}

		}

		//����һ��(0,1)֮��� �����

		double numA = (double)(rand()) / (double)(RAND_MAX);

		double numB = (double)(rand()) / (double)(RAND_MAX);



		//��[0,1]�ĵ� �Ŵ� [0,500] ֮��

		int Px = (int)(numA * 500);

		int Py = (int)(numB * 500);

		//��ʾ �����ɵĵ�

		array_of_img[Px][Py] = 255;

		// ������д��ͼ����

		WriteImageData(img_data, width_step, width_step, width_step, array_of_img, true);

		//���»�������Բ

		cvCircle(img, cvPoint(250, 250), 250, cvScalar(255), 1, 8, 0);



		//�жϸ����ɵĵ� �Ƿ��� ԰��

		if (((numA - 0.5)*(numA - 0.5) + (numB - 0.5)*(numB - 0.5)) <= 0.25)

		{

			sumCircle++;

		}

		cvShowImage("Image", img);//��ʾͼ��

		cvWaitKey(50); //��ʱ50����



		PI = (double)sumCircle / (double)count;

		PI *= 4;

		printf("%d %d\n", sumCircle, count);

		printf("The PI is : %lf\n", PI);

	}

	PI = (double)sumCircle / (double)sumSquare;

	PI *= 4;

	printf("The PI is : %lf\n", PI);

	cvDestroyWindow("Image");//���ٴ���

	cvReleaseImage(&img); //�ͷ�ͼ��



	delete[] array_of_img[0];

	delete[] array_of_img;



	return 0;

}
