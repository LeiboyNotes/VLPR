#ifndef SOBELLLOCATE_H
#define SOBELLLOCATE_H

#include "PlateLocate.h"

class SobelLocate :public PlateLocate
{
public:
	SobelLocate();
	virtual ~SobelLocate();
	/*
	*���ƶ�λ��1��ԭͼ��2�������ѡ����
	*/
	void locate(Mat src, vector<Mat>& dst_plates);

private:
};



#endif // SOBELLLOCATE_H

