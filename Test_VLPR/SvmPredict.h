#ifndef SVMPREDICT_H
#define SVMPREDICT_H

#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
using namespace ml;

class SvmPredict
{
public:
	SvmPredict(const char* svm_model);
	virtual ~SvmPredict();

	/*
	*SVMÆÀ²â
	*/
	int doPredict(vector<Mat> candi_plates, Mat &plate) ;

	

private:
	Ptr<SVM>svm;
	HOGDescriptor *svmHog=0;
	void getHogFeatures(HOGDescriptor* hog, Mat src, Mat& dst);
};



#endif // PLATELOCATE_H
