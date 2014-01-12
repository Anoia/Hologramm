/*
#include "projekt.h"
#include <io.h>

using namespace cv;
using namespace std;

static int windowWidth;
static int windowHeight;
const string imagePath = "C:/Users/Esther/Desktop/pattern.png";
static Mat img;
static int imgWidth;
static int imgHeight;
static Mat effektMat;
static	int xCount;
static	int yCount;

void doSomething(const string& videoPath){

	// ### EFFECTTHINGS ###
	img = imread(imagePath);
	imgWidth = img.cols;
	imgHeight = img.rows;
	xCount  = 0;
	yCount = 0;

	// ### VIDEOTHINGS ###

	//const string imagePath = "C:/Users/Esther/Desktop/Holo.png";

	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
	

	// Hintergrundbild laden
    Mat image = imread(imagePath);
    Mat holoImg;
    Size videoSize(width, height);
	windowWidth = width;
	windowHeight = height;

	effektMat = Mat(windowWidth, windowHeight, CV_8UC3);

    resize(image, holoImg, videoSize, 0,0);
	
	



	namedWindow("Video");
	namedWindow("Maske");
	namedWindow("Holo");
	namedWindow("Effekt");


	Mat firstFrame;
	Mat background;
	Mat videoFrameGrau(height, width, CV_8UC1);
	Mat holoBild(height, width, CV_8UC3);
	Mat maske(height, width, CV_8UC1);

	int frameNumber = 0;

	while(true){
		effekt();
		Mat videoFrame;
		if(video.read(videoFrame) == false){
			break;
		}
		
        // in Graustufen wandeln
        cvtColor(videoFrame, videoFrameGrau, CV_BGR2GRAY);                

        // erstes Frame merken
        frameNumber++;
        if(frameNumber == 1){
			videoFrameGrau.copyTo(firstFrame);
			videoFrame.copyTo(background);
        }

		// berechne pixelweise: videoFrameGrau = abs(videoFrameGrau - firstFrame)
		absdiff(videoFrameGrau, firstFrame, maske);

		threshold(maske, maske, 10, 255, THRESH_BINARY);

		background.copyTo(holoBild);
		Mat grau(height, width, CV_8UC3);
		cvtColor(videoFrameGrau, grau, CV_GRAY2BGR);

		double alpha = 0.7;
		Mat newEffektMat(height, width, CV_8UC3);
		cvtColor(effektMat, newEffektMat, CV_8UC3);
		Mat effekt = (1-alpha)*grau + alpha * newEffektMat;


		effekt.copyTo(holoBild, maske);
		
		holoBild = (1-alpha)*background + alpha * holoBild;


		imshow("Video", videoFrame);
		imshow("Maske", maske);
		imshow("Holo", holoImg);
		imshow("Effekt", holoBild);
		waitKey(30);

	}

}



void effekt(){
	
		if(xCount == imgWidth){
			xCount = 0;
		}
		if(yCount == imgHeight){
			yCount = 0;
		}


		for(int x = 0-imgWidth ; x < windowWidth + imgWidth; x++){

			for(int y = 0-imgHeight; y < windowHeight + imgHeight; y++){

				int imgx = (x+imgWidth) % imgWidth;
				int imgy = (y+imgHeight) % imgHeight;

				int newY = y + yCount;
				int newX = x + xCount;
				if(newY >= 0 && newY < windowHeight && newX >= 0 && newX < windowWidth){
					
					effektMat.at<Vec3b>(newY, newX) =  img.at<Vec3b>(imgy, imgx);
				}

				

			}
		}

		xCount++;
		yCount+=2;
	
}

void updateEffekt(){
	
}
*/