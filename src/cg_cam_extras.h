#pragma once
#ifndef CG_CAM_EXTRAS
#define CG_CAM_EXTRAS

#include "ofMain.h"
#include "cg_extras.h"

//código extraído das aulas

//calcula o frustum com base em theta, alpha e beta
inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta, bool invertX = false, bool invertY = false) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat tan = tanf(theta * 0.5 * PI / 180.0);
	GLfloat d = (gh() / 2.0) / tan;
	GLfloat nearClip = d / alpha;
	GLfloat farClip = d * beta;
	GLfloat ymax = nearClip * tan;
	GLfloat xmax = (gw() / gh()) * ymax;
	if (invertX) {
		xmax = -xmax;
	}
	if (invertY) {
		ymax = -ymax;
	}
	glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
}


//implementa o algoritmo de lookAt
inline void lookat(
	GLfloat camX,
	GLfloat camY,
	GLfloat camZ,
	GLfloat targetX,
	GLfloat targetY,
	GLfloat targetZ,
	GLfloat upX,
	GLfloat upY,
	GLfloat upZ)
{
	ofVec3f cam = ofVec3f(camX, camY, camZ);
	ofVec3f target = ofVec3f(targetX, targetY, targetZ);
	ofVec3f up = ofVec3f(upX, upY, upZ);


	ofVec3f N = cam - target;
	N = N.normalized();
	ofVec3f U = cross(up, N);
	U = U.normalized();
	ofVec3f V = cross(N, U);
	V = V.normalized();

	GLfloat camTransformMatrix[4][4] = {
		{U.x, V.x, N.x, 0},
		{U.y, V.y, N.y, 0},
		{U.z, V.z, N.z, 0},
		{-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
	};

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(&camTransformMatrix[0][0]);
}

inline void lookat(ofVec3f cam, ofVec3f look, ofVec3f up) {
	lookat(cam.x, cam.y, cam.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

#endif