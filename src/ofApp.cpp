#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

    incrementing, view = true;
    mode = false;
    move = 4.0f;
    delayCounter, camera = 0;

    resX = 30;
    resY = 30;
    floorWidth = gw() * 0.5;
    floorHeight = gw() * 0.5;
    floorHeightPos = 0.;

    cameraRadius = 200.0f;
    cameraAngle = 360.0f;

    ambientOn = true;
    dirOn = false;
    pointOn = false;
    pointOn1 = false;
    spotOn = false;
    lightPos = false;

    dirAmbOn = true;
    dirDifOn = true;
    dirSpecOn = true;
    spotAmbOn = true;
    spotDifOn = true;
    spotSpecOn = true;
    pointAmbOn = true;
    pointDifOn = true;
    pointSpecOn = true;
    pointAmbOn1 = true;
    pointDifOn1 = true;
    pointSpecOn1 = true;

    dirVecTheta = 0.;

    ofDisableArbTex();
    glShadeModel(GL_SMOOTH);

    skybox.load("Daylight Box UV.png");
    floor.load("cracked_z.png");
    tex.load("HighRiseGlass0006_1_350.jpg");
    tex1.load("HighRiseResidential0139_1_350.jpg");
    tex2.load("Texture residential building seamless 00795.jpeg");
    tex3.load("BuildingsHighRise0551_1_350.jpg");

}

//--------------------------------------------------------------
void ofApp::update(){
    //fps
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

    //rotating cylinder
    angle += 0.3f;

    //elevator
    if (delayCounter > 0) {
        delayCounter--;
    }
    else {
        if (incrementing) {
            move += 0.1f;
            if (move >= 90.0f) {
                move = 90.0f;
                incrementing = false;
                delayCounter = 60;
            }
        }
        else {
            move -= 0.1f;
            if (move <= 4.0f) {
                move = 4.0f;
                incrementing = true;
                delayCounter = 60;
            }
        }
    }

    //camera
    cameraAngle -= 0.2f;

    if (cameraAngle <= 360.0f) {
        cameraAngle += 360.0f;
    }

    cameraz = cameraRadius * cos(ofDegToRad(cameraAngle));
    camerax = cameraRadius * sin(ofDegToRad(cameraAngle));

    //calculo da direcao da luz direcional
    float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
    float y = gh() * 0.5;
    float x = 0;
    dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
    dirVecTheta += 0.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, gw(), gh());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if (view) {
        perspective(60, 20, 10000);
    }
    else {
        glOrtho(-100, 100, -60, 140, 0, 300);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (camera == 0) lookat(0, 30, 0, 0, 30, -180, 0, 1, 0);
    else if (camera == 1) lookat(220, 50, -195, 70, 50, -195, 0, 1, 0);
    else if (camera == 2) lookat(20, 260, -182, 20, 30, -182, 0, 0, -1);
    else if (camera == 3) lookat(camerax, 70, cameraz - 180, 0, 50, -160, 0, 1, 0);

    if (mode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    if (ambientOn) {
        ambientLight[0] = 1.;//R
        ambientLight[1] = 1.;//G
        ambientLight[2] = 1.;//B
        ambientLight[3] = 1;
    }
    else {
        ambientLight[0] = 0.;
        ambientLight[1] = 0.;
        ambientLight[2] = 0.;
        ambientLight[3] = 1;
    }

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    //luz direcional
    dirVec[0] = dirVec3f.x;//x
    dirVec[1] = dirVec3f.y;//y
    dirVec[2] = dirVec3f.z;//z
    dirVec[3] = 0;

    if (dirAmbOn) {
        dirAmb[0] = 1.;//R
        dirAmb[1] = 1.;//G
        dirAmb[2] = 1.;//B
        dirAmb[3] = 1.;//constante
    }
    else {
        dirAmb[0] = 0.;//R
        dirAmb[1] = 0.;//G
        dirAmb[2] = 0.;//B
        dirAmb[3] = 1.;//constante
    }

    if (dirDifOn) {
        dirDif[0] = 1.;//R
        dirDif[1] = 1.;//G
        dirDif[2] = 1.;//B
        dirDif[3] = 1.;//constante
    }
    else {
        dirDif[0] = 0.;//R
        dirDif[1] = 0.;//G
        dirDif[2] = 0.;//B
        dirDif[3] = 1.;//constante
    }

    if (dirSpecOn) {
        dirSpec[0] = 1.;//R
        dirSpec[1] = 1.;//G
        dirSpec[2] = 1.;//B
        dirSpec[3] = 1.;//constante
    }
    else {
        dirSpec[0] = 0.;//R
        dirSpec[1] = 0.;//G
        dirSpec[2] = 0.;//B
        dirSpec[3] = 1.;//constante
    }

    glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);
    if (dirOn) {
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHT0);
    }

    //luz pontual1
    pointPos[0][0] = 60;//x
    pointPos[0][1] = 150;//y
    pointPos[0][2] = -230;//z
    pointPos[0][3] = 1;

    if (pointAmbOn) {
        pointAmb[0][0] = 1.;//R
        pointAmb[0][1] = 0.;//G
        pointAmb[0][2] = 0.;//B
        pointAmb[0][3] = 1.;//constante
    }
    else {
        pointAmb[0][0] = 0.;//R
        pointAmb[0][1] = 0.;//G
        pointAmb[0][2] = 0.;//B
        pointAmb[0][3] = 1.;//constante
    }

    if (pointDifOn) {
        pointDif[0][0] = 1.;//R
        pointDif[0][1] = 0.;//G
        pointDif[0][2] = 0.;//B
        pointDif[0][3] = 1.;//constante
    }
    else {
        pointDif[0][0] = 0.;//R
        pointDif[0][1] = 0.;//G
        pointDif[0][2] = 0.;//B
        pointDif[0][3] = 1.;//constante
    }

    if (pointSpecOn) {
        pointSpec[0][0] = 1.;//R
        pointSpec[0][1] = 1.;//G
        pointSpec[0][2] = 1.;//B
        pointSpec[0][3] = 1.;//constante
    }
    else {
        pointSpec[0][0] = 0.;//R
        pointSpec[0][1] = 0.;//G
        pointSpec[0][2] = 0.;//B
        pointSpec[0][3] = 1.;//constante
    }

    glLightfv(GL_LIGHT1, GL_POSITION, pointPos[0]);
    glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb[0]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif[0]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec[0]);
    //atenuação
    pointAtC[0] = 1;
    pointAtL[0] = 0.001;
    pointAtQ[0] = 0.0001;
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, pointAtC[0]);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, pointAtL[0]);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, pointAtQ[0]);
    if (pointOn) {
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT1);
    }

    //luz pontual2
    pointPos[1][0] = 0;//x
    pointPos[1][1] = 60;//y
    pointPos[1][2] = -200;//z
    pointPos[1][3] = 1;

    if (pointAmbOn1) {
        pointAmb[1][0] = 0.;//R
        pointAmb[1][1] = 0.;//G
        pointAmb[1][2] = 1.;//B
        pointAmb[1][3] = 1.;//constante
    }
    else {
        pointAmb[1][0] = 0.;//R
        pointAmb[1][1] = 0.;//G
        pointAmb[1][2] = 0.;//B
        pointAmb[1][3] = 1.;//constante
    }

    if (pointDifOn1) {
        pointDif[1][0] = 0.;//R
        pointDif[1][1] = 0.;//G
        pointDif[1][2] = 1.;//B
        pointDif[1][3] = 1.;//constante
    }
    else {
        pointDif[1][0] = 0.;//R
        pointDif[1][1] = 0.;//G
        pointDif[1][2] = 0.;//B
        pointDif[1][3] = 1.;//constante
    }

    if (pointSpecOn1) {
        pointSpec[1][0] = 1.;//R
        pointSpec[1][1] = 1.;//G
        pointSpec[1][2] = 1.;//B
        pointSpec[1][3] = 1.;//constante
    }
    else {
        pointSpec[1][0] = 0.;//R
        pointSpec[1][1] = 0.;//G
        pointSpec[1][2] = 0.;//B
        pointSpec[1][3] = 1.;//constante
    }

    glLightfv(GL_LIGHT3, GL_POSITION, pointPos[1]);
    glLightfv(GL_LIGHT3, GL_AMBIENT, pointAmb[1]);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, pointDif[1]);
    glLightfv(GL_LIGHT3, GL_SPECULAR, pointSpec[1]);
    //atenuação
    pointAtC[1] = 1;
    pointAtL[1] = 0.001;
    pointAtQ[1] = 0.0001;
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, pointAtC[1]);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, pointAtL[1]);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, pointAtQ[1]);
    if (pointOn1) {
        glEnable(GL_LIGHT3);
    }
    else {
        glDisable(GL_LIGHT3);
    }

    //luz foco
    spotPos[0] = 54;
    spotPos[1] = 90;
    spotPos[2] = -230;
    spotPos[3] = 1;

    spotDir[0] = -1.;
    spotDir[1] = -0.45;
    spotDir[2] = 1.;

    if (spotAmbOn) {
        spotAmb[0] = 1.;//R
        spotAmb[1] = 1.;//G
        spotAmb[2] = 1.;//B
        spotAmb[3] = 0.;//constante
    }
    else {
        spotAmb[0] = 0.;//R
        spotAmb[1] = 0.;//G
        spotAmb[2] = 0.;//B
        spotAmb[3] = 0.;//constante
    }

    if (spotDifOn) {
        spotDif[0] = 1.;//R
        spotDif[1] = 1.;//G
        spotDif[2] = 1.;//B
        spotDif[3] = 1.;//constante
    }
    else {
        spotDif[0] = 0.;//R
        spotDif[1] = 0.;//G
        spotDif[2] = 0.;//B
        spotDif[3] = 1.;//constante
    }

    if (spotSpecOn) {
        spotSpecular[0] = 1.;//R
        spotSpecular[1] = 1.;//G
        spotSpecular[2] = 1.;//B
        spotSpecular[3] = 1.;//constante
    }
    else {
        spotSpecular[0] = 0.;//R
        spotSpecular[1] = 0.;//G
        spotSpecular[2] = 0.;//B
        spotSpecular[3] = 1.;//constante
    }

    //concentracao
    spotExponent = 5;//0 - 128

    //angulo
    spotCutoff = 60;//0 - 180

    glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

    glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);

    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

    //atenuação
    spotAtC = 1.;
    spotAtL = 0.;
    spotAtQ = 0.;
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);
    if (spotOn) {
        glEnable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT2);
    }

    if (lightPos) {
        glDisable(GL_LIGHTING);

        if (pointOn) {
            glColor3f(1, 1, 1);
            glPushMatrix();
            glTranslatef(pointPos[0][0], pointPos[0][1], pointPos[0][2]);
            glScalef(30, 30, 30);
            cube_unit(0.1, tex);
            glPopMatrix();
        }
        if (pointOn1){
            glColor3f(1, 1, 1);
            glPushMatrix();
            glTranslatef(pointPos[1][0], pointPos[1][1], pointPos[1][2]);
            glScalef(30, 30, 30);
            cube_unit(0.1, tex);
            glPopMatrix();
        }

        if (dirOn) {
            glColor3f(1, 1, 1);
            glPushMatrix();
            glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
            glScalef(30, 30, 30);
            cube_unit(0.1, tex);
            glPopMatrix();

            glPushMatrix();
            glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(dirVec3f.x, dirVec3f.y, dirVec3f.z);
            glEnd();
            glPopMatrix();
        }
        if (spotOn) {
            glColor3f(1, 1, 1);
            glPushMatrix();
            glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
            glScalef(30, 30, 30);
            cube_unit(0.1, tex);
            glPopMatrix();
        }

        glEnable(GL_LIGHTING);
    }

    //floor
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);

    glEnable(GL_TEXTURE);
    floor.bind();
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1, 1, 1);
    glTranslatef(0, 0, -180);
    glRotatef(90, 1, 0, 0);
    glScalef(floorWidth, floorHeight, 1.);
    glBegin(GL_QUADS);
    glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
    glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
    glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
    glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
    glEnd();
    malha_unit(resX, resY);
    floor.unbind();
    glPopMatrix();

    //buildings

    //H building
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
    
    glTranslatef(0, 0, -200);
    glColor3f(1, 0, 0);
    h_building(10, tex);
    glPopMatrix();

    //grid tower
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
    glTranslatef(-30, 50, -185);
    glColor3f(1, 0, 1);
    glScalef(30, 100, 20);
    textures(1, 2, tex1);
    cube_malha_unit(4, 4);
    glPopMatrix();

    //grid building
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
    glTranslatef(40, 7.5, -155);
    glColor3f(0, 1, 0);
    glScalef(35, 15, 35);
    textures(2, 1, tex3);
    cube_malha_unit(4, 4);
    glPopMatrix();

    //unit cube tower
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
    glTranslatef(-12, 0, -150);
    glColor3f(0, 1, 1);
    cube_unit_building(8, 2, tex3);
    glPopMatrix();

    //elevator
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
    glTranslatef(-37, move, -173);
    glColor3f(1, 1, 0);
    glScalef(4, 8, 4);
    textures(1, 1, tex);
    cube_malha_unit(1, 1);
    glPopMatrix();

    //custom tower
    glColor3f(0, 0, 1);

    glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
    std::vector<ofVec3f> bottomSquare;
    bottomSquare.push_back(ofVec3f(50, 0, -240));
    bottomSquare.push_back(ofVec3f(70, 0, -240));
    bottomSquare.push_back(ofVec3f(70, 0, -220));
    bottomSquare.push_back(ofVec3f(50, 0, -220));

    std::vector<ofVec3f> topSquare;
    topSquare.push_back(ofVec3f(55, 110, -235));
    topSquare.push_back(ofVec3f(65, 110, -235));
    topSquare.push_back(ofVec3f(65, 110, -225));
    topSquare.push_back(ofVec3f(55, 110, -225));

    customBuilding(bottomSquare, topSquare, tex);

    //top
    glColor3f(0, 0, 1);
    std::vector<ofVec3f> bottomSquareTop;
    bottomSquareTop.push_back(ofVec3f(57, 118, -233));
    bottomSquareTop.push_back(ofVec3f(63, 118, -233));
    bottomSquareTop.push_back(ofVec3f(63, 118, -227));
    bottomSquareTop.push_back(ofVec3f(57, 118, -227));

    std::vector<ofVec3f> topSquareTop;
    topSquareTop.push_back(ofVec3f(59, 136, -231));
    topSquareTop.push_back(ofVec3f(61, 136, -231));
    topSquareTop.push_back(ofVec3f(61, 136, -229));
    topSquareTop.push_back(ofVec3f(59, 136, -229));

    customBuilding(bottomSquareTop, topSquareTop ,tex);

    //rotating part
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

    glColor3f(0, 1, 1);
    glTranslatef(60, 118, -230);
    glRotatef(angle, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    drawCylinder(14, 8, 20, tex);
    glPopMatrix();

    //unit cube building
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
    glTranslatef(70, 20, -190);
    glColor3f(1, 1, 0);
    glScalef(6, 20, 6);
    cube_unit(1, tex2);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

    //skybox
    glPushMatrix();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTranslatef(0, 0, -180);
    glColor3f(1, 1, 1);

    float size = 240;
    skybox.bind();

    glBegin(GL_QUADS);
    // Front
    glTexCoord2f(0.25, 0.666666); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.5, 0.666666); glVertex3f(size, -size, -size);
    glTexCoord2f(0.5, 0.3333333); glVertex3f(size, size, -size);
    glTexCoord2f(0.25, 0.333333); glVertex3f(-size, size, -size);
    glEnd();
 
    glBegin(GL_QUADS);
    // Back
    glTexCoord2f(1, 0.666666); glVertex3f(-size, -size, size);
    glTexCoord2f(0.75, 0.666666); glVertex3f(size, -size, size);
    glTexCoord2f(0.75, 0.333333); glVertex3f(size, size, size);
    glTexCoord2f(1, 0.333333); glVertex3f(-size, size, size);
    glEnd();
 
    glBegin(GL_QUADS);
    // Left
    glTexCoord2f(0, 0.666666); glVertex3f(-size, -size, size);
    glTexCoord2f(0.25, 0.666666); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.25, 0.333333); glVertex3f(-size, size, -size);
    glTexCoord2f(0, 0.333333); glVertex3f(-size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    // Right
    glTexCoord2f(0.75, 0.666666); glVertex3f(size, -size, size);
    glTexCoord2f(0.5, 0.666666); glVertex3f(size, -size, -size);
    glTexCoord2f(0.5, 0.333333); glVertex3f(size, size, -size);
    glTexCoord2f(0.75, 0.333333); glVertex3f(size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    // Top
    glTexCoord2f(0.25, 0); glVertex3f(-size, size, size);
    glTexCoord2f(0.5, 0); glVertex3f(size, size, size);
    glTexCoord2f(0.5, 0.333333); glVertex3f(size, size, -size);
    glTexCoord2f(0.25, 0.333333); glVertex3f(-size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    // Bottom
    glTexCoord2f(0.25, 1); glVertex3f(-size, -size, size);
    glTexCoord2f(0.5, 1); glVertex3f(size, -size, size);
    glTexCoord2f(0.5, 0.666666); glVertex3f(size, -size, -size);
    glTexCoord2f(0.25, 0.666666); glVertex3f(-size, -size, -size);
    glEnd();

    skybox.unbind();

    glPopMatrix();
    glDisable(GL_TEXTURE);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case '1':
        camera = 0;
        break;
    case '2':
        camera = 1;
        break;
    case '3':
        camera = 2;
        break;
    case '4':
        cameraAngle = 360.0f;
        camera = 3;
        break;
    case 'p':
        view = !view;
        break;
    case 'o':
        mode = !mode;
        break;
    case 'a':
        ambientOn = !ambientOn;
        break;
    case 's':
        spotOn = !spotOn;
        break;
    case 'd':
        dirOn = !dirOn;
        break;
    case 'f':
        pointOn = !pointOn;
        break;
    case 'g':
        pointOn1 = !pointOn1;
        break;
    case 'i':
        lightPos = !lightPos;
        break;
    case 'q':
        pointAmbOn = !pointAmbOn;
        break;
    case 'w':
        pointDifOn = !pointDifOn;
        break;
    case 'e':
        pointSpecOn = !pointSpecOn;
        break;
    case 'r':
        pointAmbOn1 = !pointAmbOn1;
        break;
    case 't':
        pointDifOn1 = !pointDifOn1;
        break;
    case 'y':
        pointSpecOn1 = !pointSpecOn1;
        break;
    case 'z':
        dirAmbOn = !dirAmbOn;
        break;
    case 'x':
        dirDifOn = !dirDifOn;
        break;
    case 'c':
        dirSpecOn = !dirSpecOn;
        break;
    case 'v':
        spotAmbOn = !spotAmbOn;
        break;
    case 'b':
        spotDifOn = !spotDifOn;
        break;
    case 'n':
        spotSpecOn = !spotSpecOn;
        break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

void ofApp::exit() {
    skybox.clear();
    floor.clear();
    tex.clear();
    tex1.clear();
    tex2.clear();
    tex3.clear();
}