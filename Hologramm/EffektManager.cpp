#include "EffektManager.h"
#include "Effekts.h"
using namespace cv;
using namespace std;



EffektManager::EffektManager(int w, int h):
videoWidth(w),
videoHeight(h){
	
}

void EffektManager::setEffekt(int e){
	switch(e){
	case HOLO:
		effekt = new HoloEffekt(videoWidth, videoHeight);
		break;
	case GHOST: 
		effekt = new GhostEffekt(videoWidth, videoHeight);
		break;
	case SLIME: 

		break;
	case POP: 
		effekt = new PopEffekt(videoWidth, videoHeight);
		break;
	}
}

void EffektManager::updateEffekt(Mat &firstFrame, Mat &currentFrame, Mat &mask, Mat &output){
	effekt->updateEffekt(firstFrame, currentFrame, mask, output);
}

EffektManager::~EffektManager(){
	delete effekt;
}