#ifndef COLORLLOCATE_H
#define COLORLLOCATE_H

#include "PlateLocate.h"

class ColorLocate :public PlateLocate
{
public:
	ColorLocate();
	virtual ~ColorLocate();
	/*
	*���ƶ�λ��1��ԭͼ��2�������ѡ����
	*/
	void locate(Mat src, vector<Mat>& dst_plates);

private:
};



#endif // COLORLLOCATE_H

