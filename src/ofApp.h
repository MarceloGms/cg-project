#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"
#include "materiais.h"

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
	void exit();

	GLint resX, resY, delayCounter, camera;
	GLfloat floorWidth, floorHeight, floorHeightPos, move, angle, cameraz, camerax, cameraAngle, cameraRadius;
	bool incrementing, view, mode;

	bool ambientOn;
	bool dirOn;
	bool pointOn;
	bool pointOn1;
	bool spotOn;
	bool lightPos;

	bool dirAmbOn;
	bool dirDifOn;
	bool dirSpecOn;
	bool spotAmbOn;
	bool spotDifOn;
	bool spotSpecOn;
	bool pointAmbOn;
	bool pointDifOn;
	bool pointSpecOn;
	bool pointAmbOn1;
	bool pointDifOn1;
	bool pointSpecOn1;
	

	GLfloat ambientLight[4];

	GLfloat dirVec[4];
	GLfloat dirAmb[4];
	GLfloat dirDif[4];
	GLfloat dirSpec[4];
	ofVec3f dirVec3f;
	GLfloat dirVecTheta;

	GLfloat pointPos[2][4];
	GLfloat pointAmb[2][4];
	GLfloat pointDif[2][4];
	GLfloat pointSpec[2][4];
	GLfloat pointAtC[2], pointAtL[2], pointAtQ[2];

	GLfloat spotPos[4];
	GLfloat spotDir[3];
	GLfloat spotAmb[4];
	GLfloat spotDif[4];
	GLfloat spotSpecular[4];
	GLfloat spotExponent;
	GLfloat spotCutoff;
	GLfloat spotAtC, spotAtL, spotAtQ;

	ofImage skybox;
	ofImage floor;
	ofImage tex;
	ofImage tex1;
	ofImage tex2;
	ofImage tex3;

};
