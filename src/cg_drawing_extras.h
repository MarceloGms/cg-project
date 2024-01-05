#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "ofApp.h"

//função extraída das aulas
//função que desenha malha unitária com resolução mxn
inline void malha_unit(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();
}

//função extraída das aulas
inline void cube_unit(GLfloat p, ofImage tex) {
	tex.bind();
	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE);
	// Front
	glTexCoord2f(0, 0); glVertex3f(-p, -p, p);
	glTexCoord2f(0, 1); glVertex3f(-p, p, p);
	glTexCoord2f(1, 1); glVertex3f(p, p, p);
	glTexCoord2f(1, 0); glVertex3f(p, -p, p);

	// Back
	glTexCoord2f(0, 0); glVertex3f(-p, -p, -p);
	glTexCoord2f(1, 0); glVertex3f(p, -p, -p);
	glTexCoord2f(1, 1); glVertex3f(p, p, -p);
	glTexCoord2f(0, 1); glVertex3f(-p, p, -p);

	// Up
	glTexCoord2f(0, 0); glVertex3f(-p, p, -p);
	glTexCoord2f(0, 1); glVertex3f(-p, p, p);
	glTexCoord2f(1, 1); glVertex3f(p, p, p);
	glTexCoord2f(1, 0); glVertex3f(p, p, -p);

	// Down
	glTexCoord2f(0, 0); glVertex3f(-p, -p, p);
	glTexCoord2f(0, 1); glVertex3f(-p, -p, -p);
	glTexCoord2f(1, 1); glVertex3f(p, -p, -p);
	glTexCoord2f(1, 0); glVertex3f(p, -p, p);

	// Left
	glTexCoord2f(1, 0); glVertex3f(-p, -p, p);
	glTexCoord2f(0, 0); glVertex3f(-p, -p, -p);
	glTexCoord2f(0, 1); glVertex3f(-p, p, -p);
	glTexCoord2f(1, 1); glVertex3f(-p, p, p);

	// Right
	glTexCoord2f(0, 0); glVertex3f(p, -p, p);
	glTexCoord2f(0, 1); glVertex3f(p, p, p);
	glTexCoord2f(1, 1); glVertex3f(p, p, -p);
	glTexCoord2f(1, 0); glVertex3f(p, -p, -p);

	glEnd();
	tex.unbind();
}

inline void cube_unit_building(GLfloat p, GLfloat height, ofImage tex){
	glPushMatrix();
	glTranslatef(0, p, 0);
	cube_unit(p, tex);
	for (int i = 0; i < height - 1; i++) {
		glTranslatef(0, p * 2, 0);
		cube_unit(p, tex);
	}
	glPopMatrix();
}

inline void h_building(GLfloat p, ofImage tex){
	//left tower
	cube_unit_building(p, 3, tex);
	//middle
	glPushMatrix();
	glTranslatef(0, p, 0);
	glTranslatef(p * 2, p * 2, 0);
	cube_unit(p, tex);
	glPopMatrix();
	//right tower
	glPushMatrix();
	glTranslatef(2 * (p * 2), 0, 0);
	cube_unit_building(p, 3, tex);
	glPopMatrix();
}

//função extraída das aulas
//funcao que desenha cubo unitario com malha_unit()
inline void cube_malha_unit(GLint m, GLint n) {

	//tras
	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//cima
	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//baixo
	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//esquerda
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//direita
	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//frente
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	malha_unit(m, n);
	glPopMatrix();
}

inline void textures(int resX, int resY, ofImage tex) {
	glEnable(GL_TEXTURE);
	tex.bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//tras
	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	//cima
	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, 1); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	//baixo
	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	//esquerda
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	//direita
	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	//frente
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	glBegin(GL_QUADS);
	glTexCoord2f(0, resY); glVertex2f(-0.5, -0.5);
	glTexCoord2f(resX, resY); glVertex2f(0.5, -0.5);
	glTexCoord2f(resX, 0); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();
	tex.unbind();
}

//funçao extraída do chatgpt
void customBuilding(const std::vector<ofVec3f>& bottomSquare, const std::vector<ofVec3f>& topSquare, ofImage tex) {
	if (bottomSquare.size() != 4 || topSquare.size() != 4) {
		// Ensure both squares have exactly 4 vertices
		return;
	}

	tex.bind();
	glBegin(GL_QUADS);

	// Draw the sides of the building by connecting corresponding vertices
	for (int i = 0; i < 4; i++) {
		glTexCoord2d(0, 1); glVertex3f(bottomSquare[i].x, bottomSquare[i].y, bottomSquare[i].z);
		glTexCoord2d(1, 1); glVertex3f(bottomSquare[(i + 1) % 4].x, bottomSquare[(i + 1) % 4].y, bottomSquare[(i + 1) % 4].z);
		glTexCoord2d(1, 0); glVertex3f(topSquare[(i + 1) % 4].x, topSquare[(i + 1) % 4].y, topSquare[(i + 1) % 4].z);
		glTexCoord2d(0, 0); glVertex3f(topSquare[i].x, topSquare[i].y, topSquare[i].z);
	}

	glEnd();

	// Draw the top face of the building
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glTexCoord2d(0, 1); glVertex3f(bottomSquare[i].x, bottomSquare[i].y, bottomSquare[i].z);
	}
	glEnd();

	// Draw the bottom face of the building
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		float u = bottomSquare[i].x / tex.getWidth();
		float v = bottomSquare[i].y / tex.getHeight();

		glTexCoord2f(u, v);
		glVertex3f(topSquare[i].x, topSquare[i].y, topSquare[i].z);
	}
	glEnd();
	tex.unbind();
}

//funçao extraída do chatgpt
void drawCylinder(float radius, float height, int resolution, ofImage texture) {
	float angleIncrement = 360.0 / resolution;

	texture.bind();

	// Draw the bottom circle
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, 0);

	for (int i = 0; i <= resolution; i++) {
		float angle = ofDegToRad(i * angleIncrement);
		float px = radius * cos(angle);
		float py = radius * sin(angle);
		glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
		glVertex3f(px, py, 0);
	}
	glEnd();

	// Draw the top circle
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, height);

	for (int i = 0; i <= resolution; i++) {
		float angle = ofDegToRad(i * angleIncrement);
		float px = radius * cos(angle);
		float py = radius * sin(angle);
		glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
		glVertex3f(px, py, height);
	}
	glEnd();

	// Connect the circles with vertical lines
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= resolution; i++) {
		float angle = ofDegToRad(i * angleIncrement);
		float px = radius * cos(angle);
		float py = radius * sin(angle);

		glTexCoord2f(float(i) / resolution, 0);
		glVertex3f(px, py, 0);

		glTexCoord2f(float(i) / resolution, 1);
		glVertex3f(px, py, height);
	}
	glEnd();

	texture.unbind();
}

