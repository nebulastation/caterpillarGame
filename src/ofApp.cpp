#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {

	if (gameState == "start") { //if the gameState is start, load intro sounds but nothing else yet
		font.load("ocr.ttf", 135, true, true, true);
		forest.load("forest.mp3");
		forest.play();
		forest.setLoop(true);
	}
	else if (gameState == "game") { //once 'g' is pressed (see keyPressed below), load everything
		font.load("ocr.ttf", 135, true, true, true);
		quailSound.load("quail.mp3");
		finchSound.load("finch.mp3");
		kingletSound.load("kinglet.mp3");
		humSound.load("hum.mp3");
		hawkSound.load("hawk.mp3");

		leaf.load("leaf.png");

		ofSetFrameRate(25);

		gameOver = false;

		fruitX = ofRandom(50, ofGetWidth() - 50); //place fruit randomly
		fruitY = ofRandom(50, ofGetHeight() - 50);
		tailLength = 0;
		x = 80;
		y = 80;


		//*********************BIRD IMAGE LOAD*****************************
		quail.load("quail.png");
		finch.load("finch.png");
		kinglet.load("kinglet.png");
		hum.load("hum.png");
		hawk.load("hawk.png");
	}
}
void ofApp::keyPressed(int key) {
	if (key == 'g') { //this takes you from start screen to game
		gameState = "game";
		setup();
	}
	else if (gameState == "game") {
		if (key == 'w') { //snake movement
			direction = 1;
		}
		if (key == 'a') {
			direction = 2;
		}
		if (key == 's') {
			direction = 3;
		}
		if (key == 'd') {
			direction = 4;
		}
		if (key == 'q') {
			gameOver = false;
		}
	}
}
//--------------------------------------------------------------
void ofApp::update() {
	if (gameState == "start") { //nothing on start

	}
	else if (gameState == "game") {
		if (x > ofGetWidth()) { //travel thru walls
			x = 0;
		}
		if (x < 0) {
			x = ofGetWidth();
		}
		if (y < 0) {
			y = ofGetHeight();
		}
		if (y > ofGetHeight()) {
			y = 0;
		}

		//***********gameOver if touch your tail or a bird***********************************************************************************************

		if (tailX.size() > 2) {
			for (int i = 0; i < tailX.size() - 1; i++) {
				if (x <= tailX[i] + 35 && x >= tailX[i] - 35 && y <= tailY[i] + 35 && y >= tailY[i] - 35) { //+/- 25 px allowance for tail segment radius
					gameOver = true; //triggers ofClear in draw()
				}
			}
		}

		//if any x, y coordinates of any tail segment come within range of any bird, or if x, y of head touch bird, gameOver*****************************
		//case 1 snake head touches birdX[i] birdY[i]
		//case 2 tail segment touches birdX[i] birdY[i]
		if (tailX.size() > 1) {
			for (int i = 0; i < tailX.size() - 1; i++) {
				if (x >= birds[i].x && x <= birds[i].x + 175 && y >= birds[i].y && y <= birds[i].y + 175) {
					gameOver = true;
				}
				if (tailX[i] >= birds[i].x && tailX[i] <= birds[i].x + 175 && tailY[i] >= birds[i].y && tailY[i] <= birds[i].y + 175) {
					gameOver = true;
				}
			}
		}

		//*****************BIRD*UPDATE********************************
		quail.update();
		finch.update();
		kinglet.update();
		hum.update();
		hawk.update();

		leaf.update();
	}
}

void ofApp::drawFruit() {
	ofSetColor(20, 225, 170);
	//ofDrawCircle(fruitX, fruitY, 60);
	leaf.draw(fruitX, fruitY, 90, 90);
}

void ofApp::drawMovingCircle() { //snake head
	ofSetColor(15, 135, 40);
	ofDrawCircle(x, y, 60);
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (gameState == "start") { //if in start state, show start screen with instructions
		ofSetColor(0, 0, 0);
		ofPushMatrix();

		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofTranslate(30, ofGetHeight() - 1300);
		ofSetColor(10, ofMap(curve, -1, 1, 50, 240), 75);
		vector < ofPath > starts = font.getStringAsPoints("It's caterpillar grow-time!\n\neat and hear bird songs\nbut don't get eaten \nsounds from audubon.org \nwasd to nav \npress g to start >>>", true, false);
		for (int i = 0; i < starts.size(); i++) {
			vector <ofPolyline> polylines = starts[i].getOutline();
			for (int j = 0; j < polylines.size(); j++) {
				polylines[j].draw();
			}
		}
		//ofTranslate(0, 0);
		ofPopMatrix();
	}
	else if (gameState == "game") { //if in game state, draw background and run game

		int sky = ofRandom(50, 250); //draw background gradient
		ofSetColor(255, 0, 0);
		ofColor colorOne(35, 90, 50);
		ofColor colorTwo(20, 90, 130);
		ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

		drawFruit();
		drawMovingCircle();


		while (tailX.size() > tailLength) { //as long as size is greater than length, erase earliest value in the array
			tailX.erase(tailX.begin());
			tailY.erase(tailY.begin());
		}


		if (x <= fruitX + 100 && x >= fruitX - 10 && y >= fruitY - 10 && y <= fruitY + 100) {
			//every movement the snake makes, check if head coincides with fruit
			//if it does, add new values to front of array using insert
			tailLength += 1; //at this moment, tailLength is equal to tail.size, breaking the while loop
			fruitX = ofRandom(50, ofGetWidth() - 50); //generate new fruit
			fruitY = ofRandom(50, ofGetHeight() - 50);

			ofPoint p = ofPoint(birdX, birdY); //add random x, y coordinates for each new bird and push back into birds vector
			birdX = ofRandom(50, ofGetWidth() - 175);
			birdY = ofRandom(50, ofGetHeight() - 180);
			birds.push_back(p);

			int sound = ofRandom(0, 4); //sound is a random value 0 to 4, each value corresponding to a bird. with each fruit eaten, a new value is pushed onto the species vector and corresponding sound is played
			species.push_back(sound);
			if (sound == 0) {
				quailSound.play();
			}
			else if (sound == 1) {
				finchSound.play();
			}
			else if (sound == 2) {
				kingletSound.play();
			}
			else if (sound == 3) {
				humSound.play();
			}
			else if (sound == 4) {
				hawkSound.play();
			}
		}
		else {
			ofSetColor(15, 135, 40);
		}


		for (int i = 0; i < tailX.size(); i++) { //for each tail segment, draw tail segment with corresponding tailX and tailY
			ofDrawCircle(tailX[i], tailY[i], 40);
		}

		if (direction == 1) {
			y = y - 60;
			tailX.push_back(x); //add new tail segment
			tailY.push_back(y);
		}
		if (direction == 2) {
			x = x - 60;
			tailX.push_back(x);
			tailY.push_back(y);
		}
		if (direction == 3) {
			y = y + 60;
			tailX.push_back(x);
			tailY.push_back(y);
		}
		if (direction == 4) {
			x = x + 60;
			tailX.push_back(x);
			tailY.push_back(y);
		}

		//float aspect = quail.getWidth() / quail.getHeight();
		//float aspect2 = finch.getWidth() / finch.getHeight();
		//float aspect3 = kinglet.getWidth() / kinglet.getHeight();
		//float aspect4 = hum.getWidth() / hum.getHeight();
		//float aspect5 = hawk.getWidth() / hawk.getHeight();


		for (int i = 0; i < species.size(); i++) { //for all of the birds currently in the game space, draw
			ofSetColor(240, 5, 20);
			if (species[i] == 0) {
				quail.draw(birds[i].x, birds[i].y, 175, 175);
			}
			else if (species[i] == 1) {
				finch.draw(birds[i].x, birds[i].y, 175, 175);
			}
			else if (species[i] == 2) {
				kinglet.draw(birds[i].x, birds[i].y, 175, 175);
			}
			else if (species[i] == 3) {
				hum.draw(birds[i].x, birds[i].y, 175, 175);
			}
			else if (species[i] == 4) {
				hawk.draw(birds[i].x, birds[i].y, 175, 175);
			}
		}

		//on gameOver, prompt game over / start over screen, press 'q' to start over

		if (gameOver == true) {
			/*ofClear(0, 0, 0);*/
			ofSetColor(0, 0, 0);
			ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

			ofTranslate(30, ofGetHeight() - 1800);
			ofSetColor(255, 0, 0);
			quail.draw(ofGetWidth() * 3 / 4, 170, 190, 190);
			finch.draw(ofGetWidth() * 3 / 4, 370, 190, 190);
			kinglet.draw(ofGetWidth() * 3 / 4, 620, 190, 190);
			hum.draw(ofGetWidth() * 3 / 4, 860, 190, 190);
			hawk.draw(ofGetWidth() * 3 / 4, 1073, 195, 195);
			vector < ofPath > paths = font.getStringAsPoints("game over\n\nbirds: california quail \npurple finch \ngolden-crowned kinglet \nrufous hummingbird \nsharp-shinned hawk \n\npress q to start again >>>", true, false);
			for (int i = 0; i < paths.size(); i++) {
				vector <ofPolyline> polylines = paths[i].getOutline();
				for (int j = 0; j < polylines.size(); j++) {
					polylines[j].draw();
				}

				ofTranslate(0, 0);
				tailLength = 0; //clear
				tailY.clear();
				tailX.clear();
				fruitX = ofRandom(0, ofGetWidth()); //generate new fruit
				fruitY = ofRandom(0, ofGetHeight());

				birds.clear();
				species.clear();

			}
		}
	}
}

void ofApp::startScreen() {

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
