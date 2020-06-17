#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void startScreen();
	string gameState = "start";

	void drawFruit();
	void drawMovingCircle();

	vector <float> tailX;
	vector <float> tailY;

	bool gameOver;
	float x, y, fruitX, fruitY;
	int tailLength = 0;

	int direction = 0;

	ofTrueTypeFont font;

	ofImage quail;
	ofImage finch;
	ofImage kinglet;
	ofImage hum;
	ofImage hawk;

	vector <ofPoint> birds;
	float birdX, birdY;

	vector <int> species;

	float curve = sin(ofGetElapsedTimef());

	ofSoundPlayer quailSound;
	ofSoundPlayer finchSound;
	ofSoundPlayer kingletSound;
	ofSoundPlayer humSound;
	ofSoundPlayer hawkSound;

	ofSoundPlayer forest;

	ofImage leaf;

};
