#ifndef COLORLLOCATE_H
#define COLORLLOCATE_H

#include "PlateLocate.h"

class ColorLocate :public PlateLocate
{
public:
	ColorLocate();
	virtual ~ColorLocate();
	/*
	*车牌定位：1、原图，2、输出候选车牌
	*/
	void locate(Mat src, vector<Mat>& dst_plates);

private:
};



#endif // COLORLLOCATE_H

