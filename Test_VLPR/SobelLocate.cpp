#include "SobelLocate.h"

SobelLocate::SobelLocate()
{
}

SobelLocate::~SobelLocate()
{
}
/*
*����ʶ�𣺳��ƶ�λ+���+�ַ�ʶ��
*/
void SobelLocate::locate(Mat src, vector<Mat>& dst_plates)
{
	//1����˹ģ��
	Mat blur;
	//opencvֻ���������뾶���뾶Խ��Խģ��
	GaussianBlur(src, blur,Size(5,5),0);
	imshow("ԭͼ", src);
	//imshow("��˹ģ��", blur);
	//2���ҶȻ�
	Mat gray;
	cvtColor(blur, gray, COLOR_BGR2GRAY);
	//imshow("�ҶȻ�", gray);
	//3��Sobel����
	Mat sobel_16;
	//����ͼ��ʱ8λ��
	//Sobel�����󵼺󣬵������ܵ�ֵ�����255��С��0
	Sobel(gray, sobel_16,CV_16S,1,0);
	//imshow("sobel", sobel_16);//�޷���ʾ
	Mat sobel;
	convertScaleAbs(sobel_16, sobel);
	//imshow("sobel", sobel);

	//4����ֵ�����Ǻڼ��ף�
	Mat shold;
	threshold(sobel, shold,0,255,THRESH_OTSU+THRESH_BINARY);
	//imshow("��ֵ��", shold);

	//5����̬ѧ�������ղ���
	Mat close;
	Mat element = getStructuringElement(MORPH_RECT,Size(17,3));
	morphologyEx(shold,close,MORPH_CLOSE,element);
	//imshow("�ղ���", close);

	//6��������
	vector<vector<Point>> contours;
	findContours(close, //����ͼ��
		contours, //�������
		RETR_EXTERNAL, //������
		CHAIN_APPROX_NONE);//�������������ص�
	RotatedRect rotateRect;
	vector<RotatedRect> vec_sobel_rects;
	//7���������жϾ��γߴ�
	Mat src_clone = src.clone();

	/*
	vector<vector<Point>>::iterator it = contours.begin();
	while (it != contours.end()) {
		rotateRect = minAreaRect(point);
		//rectangle(src_clone, rotateRect.boundingRect(), Scalar(0, 0, 255));
		if (verifySizes(rotateRect)) {
			vec_sobel_rects.push_back(rotateRect);
			++it;
		}
		else {
			it = contours.erase(it);
		}
	}
	*/

	for each (vector<Point> point in contours)
	{
		rotateRect = minAreaRect(point);
		//rectangle(src_clone, rotateRect.boundingRect(), Scalar(0, 0, 255));
		if (verifySizes(rotateRect)) {
			vec_sobel_rects.push_back(rotateRect);
		}
		
	}

	for each (RotatedRect rect in vec_sobel_rects)
	{
		//rectangle(src_clone, rect.boundingRect(), Scalar(0, 255, 0));
	}
	//imshow("������", src_clone);

	//8�����ν���
	tortuosity(src, vec_sobel_rects, dst_plates);
	for each (Mat m in dst_plates)
	{
		//imshow("������", m);
		//waitKey();
	}

	//waitKey();


	blur.release();
	gray.release();
	sobel_16.release();
	sobel.release();
	shold.release();
	close.release();
	element.release();
	src_clone.release();


}
