#ifndef WEBCAMEFFEKTE_H
#define WEBCAMEFFEKTE_H

#include "VideoManager.h"



class Webcameffekte{
public:
	Webcameffekte();
	~Webcameffekte();
private:
	VideoManager* vm;
	std::string path;
	void menu();
	void start();
	void useWebcam();
	void useVideo();
	void createVideomanager();
	void selectEffekt();
};

#endif