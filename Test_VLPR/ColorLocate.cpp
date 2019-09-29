
#include "ColorLocate.h"

ColorLocate::ColorLocate()
{
}

ColorLocate::~ColorLocate()
{
}

void ColorLocate::locate(Mat src, vector<Mat>& dst_plates)
{

	//1��Ԥ����
	//srcĿǰ��BGR��ɫ�ռ䣬ת����HSV
	Mat hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	//imshow("hsv", hsv);
	//����ɫ���� ��h(100-124)  s(43-255)  v(46-255)
	//����
	//��ȡͨ����
	int channels = hsv.channels();
	int height = hsv.rows;
	int width = hsv.cols * channels;

	if (hsv.isContinuous()) {//����������洢������1��������
		width *= height;
		height = 1;
	}
	uchar* p;
	for (int i = 0; i < height; i++) {
		p = hsv.ptr<uchar>(i);//ȡ��i�е�����
		for (int j = 0; j < width; j+=3)//ÿ�δ���3�����ݣ�����j����Ϊ3
		{
			//��ȡ h s v����
			int h = p[j];
			int s = p[j+1];
			int v = p[j+2];
			bool isBlue = false;
			//h(100-124)  s(43-255)  v(46-255)
			if (h >= 100 && h <= 124 &&
				s >= 43 && h <= 255 &&
				v >= 46 && v <= 255) {
				isBlue = true;
			}
			if (isBlue) {
				//͹����ɫ��V�������255��
				p[j] = 0;//h
				p[j+1] = 0;//s
				p[j+2] = 255;//v
			}
			else {
				//��ڣ�V����Ϊ0��
				p[j] = 0;//h
				p[j + 1] = 0;//s
				p[j + 2] = 0;//v
			}
		}
		
	}//end for
	//imshow("͹����ɫ", hsv);
	vector<Mat>hsv_split;
	split(hsv, hsv_split);//��ͼ��ͨ�����з���    merge()�ϲ�
	//imshow("����V����", hsv_split[2]);


	Mat shold;


	//��ɫ���ƣ��ַ�ǳ���������ֵ��
	//��ɫ���ƣ��ַ����ǳ������ֵ��
	threshold(hsv_split[2], shold, 0, 255, THRESH_OTSU + THRESH_BINARY);
	//imshow("��ֵ��", shold);



	Mat close;
	Mat element = getStructuringElement(MORPH_RECT, Size(17, 3));
	morphologyEx(shold, close, MORPH_CLOSE, element);
	imshow("�ղ���", close);

	//������
	vector<vector<Point>> contours;
	findContours(close, //����ͼ��
		contours, //�������
		RETR_EXTERNAL, //������
		CHAIN_APPROX_NONE);//�������������ص�
	RotatedRect rotateRect;
	vector<RotatedRect> vec_color_rects;
	//�������жϾ��γߴ�
	Mat src_clone = src.clone();
	for each (vector<Point> point in contours)
	{
		rotateRect = minAreaRect(point);
		//rectangle(src_clone, rotateRect.boundingRect(), Scalar(0, 0, 255));
		if (verifySizes(rotateRect)) {
			vec_color_rects.push_back(rotateRect);
		}

	}

	for each (RotatedRect rect in vec_color_rects)
	{
		//rectangle(src_clone, rect.boundingRect(), Scalar(0, 255, 0));
	}
	//imshow("color������", src_clone);

	//���ν���
	tortuosity(src, vec_color_rects, dst_plates);
	for each (Mat m in dst_plates)
	{
		//imshow("color��λ��ѡ����", m);
		//waitKey();
	}

	for (Mat m : hsv_split) {
		m.release();
	}
	hsv.release();
	shold.release();
	close.release();
	element.release();
	src_clone.release();
}
