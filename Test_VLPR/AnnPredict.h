#ifndef ANNPREDICT_H
#define ANNPREDICT_H

#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
using namespace ml;

class AnnPredict
{
public:
	AnnPredict(const char* ann_model, const char* ann_zh_model);
	virtual ~AnnPredict();

	/*
	*SVMÆÀ²â
	*/
	String doPredict(Mat plate);



private:
	Ptr<ANN_MLP>ann;//Êý×Ö+×ÖÄ¸
	Ptr<ANN_MLP>ann_zh;//ÖÐÎÄ
	HOGDescriptor* annHog = 0;
	void getHogFeatures(HOGDescriptor* hog, Mat src, Mat& dst);
	bool clearMaoDing(Mat &plate);
	bool verifyCharSize(Mat plate);
	int getCityIndex(vector<Rect> vec_ann_rects);
	void getChineseRect(Rect city, Rect& chineseRect);
	void predict(vector<Mat> vec, string& result);
	static string ZHCHARS[];
	static char CHARS[];

};



#endif // ANNPREDICT_H
