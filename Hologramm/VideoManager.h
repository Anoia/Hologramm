#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <string>
#include <opencv2\opencv.hpp>
#include "Effekt.h"
#include "EffektManager.h"
#include "Maskierung.h"
/**
	Der VideoManager ist für das Laden und Abspielen des ausgewählten Videos zuständig. 
	Er lädt die Videodatei und liest nach und nach die Frames.
	Für jeden Frame wird die Maske berechnet
	
*/
class VideoManager{
public:
	VideoManager(const std::string &path, int effekt);
	~VideoManager();

	bool update();

private:
	
	EffektManager* effektManager;
	Maskierung* maskierung;

	cv::Mat firstFrame;
	cv::VideoCapture videoCapture;

	int videoWidth;
	int videoHeight;
	int frameNumber;

	void playVideo(cv::Mat &currentFrame);
	void applyEffekt(cv::Mat &currentFrame, cv::Mat &output);
	void calculateMask(cv::Mat &currentFrame, cv::Mat &output);
	void findLargestArea(cv::Mat &mask);
};

#endif