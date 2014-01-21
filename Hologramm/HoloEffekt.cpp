#include "HoloEffekt.h"


using namespace cv;

HoloEffekt::HoloEffekt(int w, int h): 
	videoWidth(w), 
	videoHeight(h),
	sourceImagePath("../resources/pattern2.png"),
	moveXCounter(0),
	moveYCounter(0){
		sourceImagePointer = new Mat(imread(sourceImagePath));		
}

	

void HoloEffekt::updateEffekt(Mat &firstFrame, Mat &currentFrame, Mat &mask, Mat &output){
	
	Mat effekt(videoHeight, videoWidth, CV_8UC3);
	applyEffektToCurrentFrame(currentFrame, effekt);
	
	//schreibt fristFrame als Hintergrund 
	firstFrame.copyTo(output);
	//Schreibt den angewendeten Effekt und wendet dabei die Maske an
	effekt.copyTo(output, mask);

	//Blendet den Hintergrund mit dem bisherigen Ergebnis, um den Effekt etwas transparent zu machen
	blend(output, firstFrame, output, 0.8);

}

/**
	Wendet die EffektMat auf den kompletten aktuellen Frame an
*/
void HoloEffekt::applyEffektToCurrentFrame(Mat &currentFrame, Mat &output){
	
	Mat effektMat(videoHeight, videoWidth, CV_8UC3);
	calculateEffektMat(effektMat);

	//konvertiert aktuellen Frame in Graustufen, dann wieder in 3-Channel-Mat
	Mat currentFrameGrau(videoHeight, videoWidth, CV_8UC1); 
	cvtColor(currentFrame, currentFrameGrau, CV_BGR2GRAY);
	cvtColor(currentFrameGrau, currentFrameGrau, CV_GRAY2BGR);

	//Blendet die EffektMat und den aktuellen Frame zusammen
	blend(effektMat, currentFrameGrau, output, 0.7);
	
	
}

/**
	blendet zwei MatObjekte zusammen
	gegebener Alphawert wird auf input1 angewendet
*/
void HoloEffekt::blend(Mat &input1, Mat &input2, Mat &output, double alpha){
	output = (1-alpha) * input2 + alpha * input1;
}

/**
	berechnet die aktuelle EffektMat
*/
void HoloEffekt::calculateEffektMat(Mat &output){
	Mat sourceImg = *sourceImagePointer;
	
	int sourceImgWidth = sourceImg.cols;
	int sourceImgHeight = sourceImg.rows;
	
	
	//zählt wie oft img nach unten bzw rechts geschoben werden muss, 
	//bis es von vorne anfängt
	if(moveXCounter == sourceImgWidth){
		moveXCounter = 0;
	}
	if(moveYCounter == sourceImgHeight){
		moveYCounter = 0;
	}

	//Zeichnet die aktuelle EffektMat
	for(int x = (0 - sourceImgWidth); x < (videoWidth + sourceImgWidth); x++){
		for(int y = (0 - sourceImgHeight); y < (videoHeight + sourceImgHeight); y++){

			//finde richtige pixel in src img für aktuelle position im effekt
			int sourcePixelX = (x + sourceImgWidth) % sourceImgWidth;
			int sourcePixelY = (y + sourceImgHeight) % sourceImgHeight;

			//wende die aktuelle Verschiebung an
			int newPositionX = x + moveXCounter;
			int newPositionY = y + moveYCounter;

			//wenn newPos nicht ausserhalb der EffektMat
			if(newPositionX >= 0
				&& newPositionX < videoWidth
				&& newPositionY >= 0
				&& newPositionY < videoHeight){

					//Schreibe sourceImgPixel in EffektMat
					output.at<Vec3b>(newPositionY, newPositionX) = sourceImg.at<Vec3b>(sourcePixelY, sourcePixelX);


			}
		}
	}

	moveXCounter++;
	moveYCounter++;
}


HoloEffekt::~HoloEffekt(void){
	delete sourceImagePointer;
}


