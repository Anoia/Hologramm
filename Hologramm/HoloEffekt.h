#ifndef HOLOEFFEKT_H
#define HOLOEFFEKT_H

#include "Effekt.h"
#include <string>

class HoloEffekt: public Effekt {
public:
	HoloEffekt(int w, int h);
	~HoloEffekt();
	void updateEffekt(cv::Mat &firstFrame, cv::Mat &currentFrame, cv::Mat &mask, cv::Mat &output);
	

private:
	void blend(cv::Mat &input1, cv::Mat &input2, cv::Mat &output, double alpha);
	void calculateEffektMat(cv::Mat &output);
	void applyEffektToCurrentFrame(cv::Mat &currentFrame, cv::Mat &output);
	const std::string sourceImagePath;
	cv::Mat* sourceImagePointer;
	int videoWidth;
	int videoHeight;
	int moveXCounter;
	int moveYCounter;
};



#endif