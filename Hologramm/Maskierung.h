#ifndef MASKIERUNG_H
#define MASKIERUNG_H

#include <opencv2\opencv.hpp>

/**
	erzeugt eine Maske, mit der die Bewegten Teile eines Bildes ausgewählt werden können
*/

class Maskierung{
public:
	Maskierung(cv::Mat &firstFrame, int videoWidth, int videoHeight);
	~Maskierung();
	void calculateMask(cv::Mat &currentFrame, cv::Mat &output);
private:
	cv::Mat firstFrame;
	int videoWidth;
	int videoHeight;

	//schwelle für erstellung der maske
	const int schwelle;
	//kSize für den medianBlur
	const int kSize;

	void findLargestArea(cv::Mat &mask);

};

#endif