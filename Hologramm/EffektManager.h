#ifndef EFFEKTMANAGER_H
#define EFFEKTMANAGER_H

#include <opencv2\opencv.hpp>
#include <string>
#include "Effekt.h"
#include "HoloEffekt.h"
#include "PopEffekt.h"
#include "GhostEffekt.h"

/**
	Der Effektmanager agiert als Context für die verschiedenen Implementationen der Effekte.
*/

class EffektManager{
public:
	EffektManager(int w, int h);
	~EffektManager();
	void setEffekt(int e);
	void updateEffekt(cv::Mat &firstFrame, cv::Mat &currentFrame, cv::Mat &mask, cv::Mat &output);

private:
	Effekt* effekt;
	int videoWidth;
	int videoHeight;
};

#endif