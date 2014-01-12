#include "Maskierung.h"

using namespace cv;

Maskierung::Maskierung(Mat &firstFrame, int videoWidth, int videoHeight):
	firstFrame(firstFrame),
	videoWidth(videoWidth),
	videoHeight(videoHeight),
	schwelle(20),
	kSize(5){
	
}

void Maskierung::calculateMask(Mat &currentFrame, Mat &mask){
	//aktuellen Frame in Grau umwandeln
	Mat currentFrameGrau(videoHeight, videoWidth, CV_8UC1);
	cvtColor(currentFrame, currentFrameGrau, CV_BGR2GRAY);

	//ersten Frame in Grau umwandeln
	Mat firstFrameGrau(videoHeight, videoWidth, CV_8UC1);
	cvtColor(firstFrame, firstFrameGrau, CV_BGR2GRAY);

	//absolute Differenz vom ersten und vom aktuellen Frame
	absdiff(currentFrameGrau, firstFrameGrau, mask);
	//mit Schwellenwert das Binärbild berechnen
	threshold(mask, mask, schwelle, 255, THRESH_BINARY);
	//medianBlur Filter anwenden, um die Kanten zu glätten
	medianBlur(mask, mask, kSize);
	//größten zusammenhängenden Bereich auswählen
	findLargestArea(mask);
}

void Maskierung::findLargestArea(Mat &mask){
	// Kopie der Maske erstellen, da findContours das Bild manipuliert
	Mat copyOfMask;
	mask.copyTo(copyOfMask);
	// alle Regionen finden
	vector<vector<Point> >contours;
	findContours(copyOfMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	// Index der Region mit der groessten Flaeche finden
	int maxArea = 0;
	int maxAreaIndex = 0;
	for(int i = 0; i < contours.size(); i++){
		vector<Point>contour = contours[i];
		int area = contourArea(contour);
		if (maxArea < area){
			maxArea = area;
			maxAreaIndex = i;
		}
	}
	// alle kleineren Regionen loeschen
	for(int i = 0; i < contours.size(); i++){
		if (i != maxAreaIndex){
			drawContours(mask, contours, i, Scalar(0, 0, 0, 0), CV_FILLED);
		}
	}	
}


Maskierung::~Maskierung(){
	
}