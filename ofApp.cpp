#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
} 

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	ofMesh face_mesh, frame_mesh;
	frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	for (auto radius = 50; radius < 300; radius += 20) {

		ofPushMatrix();

		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		for (auto deg = 0; deg < 360; deg++) {

			auto index = face_mesh.getVertices().size();
			vector<glm::vec3> vertices;

			auto z = radius * 0.05 * sin((deg + ofGetFrameNum() * 0.5) * 15 * DEG_TO_RAD);
			vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z - 10));
			vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z + 10));
			z = radius * 0.05 * sin((deg + ofGetFrameNum() * 0.5 + 1) * 15 * DEG_TO_RAD);
			vertices.push_back(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), z + 10));
			vertices.push_back(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), z - 10));

			face_mesh.addVertices(vertices);
			face_mesh.addIndex(index + 0); face_mesh.addIndex(index + 1); face_mesh.addIndex(index + 2);
			face_mesh.addIndex(index + 0); face_mesh.addIndex(index + 2); face_mesh.addIndex(index + 3);

			frame_mesh.addVertices(vertices);
			frame_mesh.addIndex(index + 0); frame_mesh.addIndex(index + 3);
			frame_mesh.addIndex(index + 1); frame_mesh.addIndex(index + 2);
		}

		ofSetColor(239);
		face_mesh.drawFaces();

		ofSetColor(39);
		frame_mesh.drawWireframe();

		face_mesh.clear();
		frame_mesh.clear();
		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}