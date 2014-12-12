#pragma once

#include "ofMain.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"

using Poco::Process;
using Poco::ProcessHandle;

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void startRecorder();
        void stopRecorder();

		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;

        bool isRecording;
        ProcessHandle* ph;
		//static ProcessHandle &recph; // process handler for recorder
};
