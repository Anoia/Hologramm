#ifndef EFFEKT_H
#define EFFEKT_H

#include <opencv2\opencv.hpp>

/**
	Effekt ist eine rein virtuelle Klasse und dient als Interface im StrategyPattern
	Dadurch werden alle abgeleiteten Klassen als Effekte gekapselt, auf jedem Effekt kann die
	Memberfunktion updateEffekt() aufgerufen werden.
*/

class Effekt{
public:
	virtual ~Effekt(){}; //Virtueller Destruktor; benötigt damit bei delete auf Objekt des Types Effekt 
						 //der Destuktor der abgeleiteten Klasse aufgerufen wird
	virtual void updateEffekt(cv::Mat &firstFrame, cv::Mat &currentFrame, cv::Mat &mask, cv::Mat &output) = 0;
};


#endif