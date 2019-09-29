// Test_VLPR.cpp: 定义应用程序的入口点。
//

#include "PlateRecognize.h"





int main()
{
	
	Mat src = imread("F:/VisualStudioProject/素材/人脸识别/Test/test1.jpg");
	//imshow("src", src);

	PlateRecognize pr("F:/VisualStudioProject/素材/人脸识别/svm.xml");
	string str_plate =  pr.recognize(src);
	cout << "车牌："<<str_plate << endl;

	waitKey();
	return 0;
}
