#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;

	isRecording = false;

    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}

	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);

	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(100,100,100);

	vidGrabber.update();

	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoInverted[i] = 255 - pixels[i];
		}
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
}


void ofApp::startRecorder() {
    // avoid re-entry
    if(isRecording) {
        ofLogNotice() << "We are already recording" << endl;
        return;
    }

    // prepare for recording
    string cmd;
    cmd = ofToDataPath( "record.sh", true );

    ofLogNotice() << "path to script: " << cmd << endl;

    std::vector<std::string> args;
    args.push_back("-ax");

    Poco::Pipe outPipe;
    ProcessHandle recph  = Process::launch(cmd, args, 0, &outPipe, 0);
    ph = (ProcessHandle*)&recph;

    ofLogNotice() << "pid of recording process " << recph.id() << endl;
    isRecording = true;
}



void ofApp::stopRecorder() {
    // request termination of external recording process
    ofLogNotice() << "Stopping the recording process..." << endl;
    Process::requestTermination( ph->id() );
    isRecording = false;
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

	if (key == ' '){
        if(isRecording) {
            stopRecorder();
        } else {
            startRecorder();
        }
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
