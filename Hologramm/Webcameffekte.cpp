#include "Webcameffekte.h"
#include "VideoManager.h"
#include <opencv2\opencv.hpp>
#include <string>
#include <io.h>
#include "Effekts.h";

using namespace std;
using namespace cv;

Webcameffekte::Webcameffekte(){
	path = "";
	menu();
}

//Zeigt ein Menü an in dem der Benutzer zwischen Webcam und Video wählen kann. 
void Webcameffekte::menu(){
	String eingabe = "";

	cout << "Hallo!" << endl;
	cout << "Bitte waehlen Sie aus, ob Sie eine Webcam oder ein Video verwenden moechten." << endl;
	while(eingabe == ""){
		cout << "C fuer Webcam" << endl;
		cout << "V fuer Video" << endl;
		cout << endl;
		cin >> eingabe;
		if(eingabe == "C" || eingabe == "c"){
			cout << "Webcam" << endl;
			useWebcam();
		}else if(eingabe == "V" || eingabe == "v"){
			cout << "Video" << endl;
			useVideo();
		}else{
			cout << endl;
			cout << "Bitte waehlen Sie zwischen Webcam und Video." << endl;
			cout << endl;
			eingabe = "";
		}
	}
	
}

//informiert den Benuzter, dass der erste Frame leer sein muss
void Webcameffekte::useWebcam(){
	cout << endl;
	cout << "Der erste Frame der Aufnahme muss leer sein." << endl;
	cout << "Bitte gehen Sie aus dem Bild der Webcam und druecken sie irgendeine Taste." << endl;
	String eingabe;
	cin >> eingabe;
	selectEffekt();

}

//Fragt nach dem Pfad für das Video
void Webcameffekte::useVideo(){
	cout << endl;
	cout << "Bitte geben Sie den Pfad des Videos an oder ziehen Sie das gewuenschte Video in dieses Fenster." << endl << endl;
	cin >> path;
	selectEffekt();
}

//Lässt den Benutzer den gewünschten Effekt wählen
void Webcameffekte::selectEffekt(){
	cout << endl;
	cout << "Bitte waehlen sie den gewuenschten Effekt aus: " << endl;
	cout << "H fuer Holografischen Effekt" << endl;
	cout << "G fuer Geistereffekt" << endl;
	cout << "P fuer Popeffekt" << endl;
	string eingabe;
	cin >> eingabe;

	int effekt = HOLO; //HOLO als default
	if(eingabe == "H" || eingabe == "h"){
		effekt = HOLO;
	}else if(eingabe == "G" || eingabe == "g"){
		effekt = GHOST;
	}else if(eingabe == "P" || eingabe == "p"){
		effekt = POP;
	}

	vm = new VideoManager(path, effekt);

	start();

}

//updatet den videoManager solange das video läuft
void Webcameffekte::start(){
	VideoManager vmObj = *vm;
	while(waitKey(30) == -1){

		if(vmObj.update() !=true){
			
			break;
		}

	}
}

//destruktor
Webcameffekte::~Webcameffekte(){
	delete vm; //gibt den speicher frei
}