#include "PopEffekt.h"

using namespace cv;

PopEffekt::PopEffekt(int w, int h):
videoWidth(w),
videoHeight(h){
	
}

void PopEffekt::updateEffekt(Mat &firstFrame, Mat &currentFrame, Mat &mask, Mat &output){
	firstFrame.copyTo(output);
	Mat effekt(videoHeight, videoWidth, CV_8UC3);
	Scalar s(255, 255, 255);
	
	effekt = s - currentFrame;
	effekt.copyTo(output, mask);

}

PopEffekt::~PopEffekt(){
	
};