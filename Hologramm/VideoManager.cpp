#include "VideoManager.h"
#include "Effekts.h"

using namespace std;
using namespace cv;


VideoManager::VideoManager(const string &path, int effekt):
frameNumber(0){

	//entscheide ob pfad oder webcam öffnen
	if(path != ""){
		videoCapture.open(path);
	}else{
		videoCapture.open(CV_CAP_ANY);
	}
	
	videoWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	videoHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

	//erstelle einen neuen Effektmanager
	effektManager = new EffektManager(videoWidth, videoHeight);
	effektManager->setEffekt(effekt);


}


bool VideoManager::update(){

	Mat currentFrame;
	if(videoCapture.read(currentFrame) == false){
		return false;
	}

	//save first Frame
	frameNumber++;
	if(frameNumber == 1){
		currentFrame.copyTo(firstFrame);
		//erstelle ein neues maskierungsobjekt, falls dies der erste frame ist
		maskierung = new Maskierung(firstFrame, videoWidth, videoHeight);
	}
	
	//maskierungsobjekt erstellt maske aus currentFrame und firstFrame und schreibt sie in mask
	Mat mask(videoHeight, videoWidth, CV_8UC1);
	maskierung->calculateMask(currentFrame, mask);

	//der Effektmanager wendet den ausgewählten effekt auf den aktuellen frame an und liefert das Endbild
	Mat result (videoHeight, videoWidth, CV_8UC3);
	effektManager->updateEffekt(firstFrame, currentFrame, mask, result);

	//Aktuelles Matobjekt anzeigen
	playVideo(result);
	
	return true;
}



void VideoManager::playVideo(Mat &currentFrame){
	namedWindow("v");
	imshow("v", currentFrame);
}

VideoManager::~VideoManager(){
	delete effektManager;
	delete maskierung;

}