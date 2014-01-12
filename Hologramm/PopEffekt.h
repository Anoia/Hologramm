#ifndef POPEFFEKT_H
#define POPEFFEKT_H

#include "Effekt.h"

class PopEffekt: public Effekt{
public:
	PopEffekt(int w, int h);
	~PopEffekt();
	void updateEffekt(cv::Mat &firstFrame, cv::Mat &currentFrame, cv::Mat &mask, cv::Mat &output);

private:
	int videoWidth;
	int videoHeight;
};

#endif