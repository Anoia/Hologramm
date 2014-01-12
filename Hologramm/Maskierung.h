#ifndef MASKIERUNG_H
#define MASKIERUNG_H

#include <opencv2\opencv.hpp>

/**
	erzeugt eine Maske, mit der die Bewegten Teile eines Bildes ausgew�hlt werden k�nnen
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

	//schwelle f�r erstellung der maske
	const int schwelle;
	//kSize f�r den medianBlur
	const int kSize;

	void findLargestArea(cv::Mat &mask);

};

#endif