#include "SobelLocate.h"

SobelLocate::SobelLocate()
{
}

SobelLocate::~SobelLocate()
{
}
/*
*车牌识别：车牌定位+检测+字符识别
*/
void SobelLocate::locate(Mat src, vector<Mat>& dst_plates)
{
	//1、高斯模糊
	Mat blur;
	//opencv只接受奇数半径，半径越大越模糊
	GaussianBlur(src, blur,Size(5,5),0);
	imshow("原图", src);
	//imshow("高斯模糊", blur);
	//2、灰度化
	Mat gray;
	cvtColor(blur, gray, COLOR_BGR2GRAY);
	//imshow("灰度化", gray);
	//3、Sobel运算
	Mat sobel_16;
	//输入图像时8位的
	//Sobel函数求导后，导数可能的值会大于255或小于0
	Sobel(gray, sobel_16,CV_16S,1,0);
	//imshow("sobel", sobel_16);//无法显示
	Mat sobel;
	convertScaleAbs(sobel_16, sobel);
	//imshow("sobel", sobel);

	//4、二值化（非黑即白）
	Mat shold;
	threshold(sobel, shold,0,255,THRESH_OTSU+THRESH_BINARY);
	//imshow("二值化", shold);

	//5、形态学操作：闭操作
	Mat close;
	Mat element = getStructuringElement(MORPH_RECT,Size(17,3));
	morphologyEx(shold,close,MORPH_CLOSE,element);
	//imshow("闭操作", close);

	//6、找轮廓
	vector<vector<Point>> contours;
	findContours(close, //输入图像
		contours, //输出轮廓
		RETR_EXTERNAL, //外轮廓
		CHAIN_APPROX_NONE);//轮廓上所有像素点
	RotatedRect rotateRect;
	vector<RotatedRect> vec_sobel_rects;
	//7、遍历并判断矩形尺寸
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
	//imshow("找轮廓", src_clone);

	//8、矩形矫正
	tortuosity(src, vec_sobel_rects, dst_plates);
	for each (Mat m in dst_plates)
	{
		//imshow("找轮廓", m);
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
