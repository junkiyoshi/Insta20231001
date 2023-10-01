#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 200; i++) {

		this->location_list.push_back(glm::vec2(ofRandom(-360, 360), ofRandom(-360, 360)));
		this->life_list.push_back(0);

		color.setHsb(ofRandom(255), 255, 255);
		this->color_list.push_back(color);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (abs(this->location_list[i].x) > 300 || abs(this->location_list[i].y) > 300) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.008, this->location_list[i].y * 0.008, ofGetFrameNum() * 0.02), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(10 * cos(deg * DEG_TO_RAD), 10 * sin(deg * DEG_TO_RAD));

		auto size = this->life_list[i] < 10 ? ofMap(this->life_list[i], 0, 20, 0, 1) : 2;

		ofSetColor(this->color_list[i], 64);
		ofDrawCircle(this->location_list[i], size);

		this->location_list[i] = next;
		this->life_list[i]++;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}