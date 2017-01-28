// main file 
//#define GLEW_STATIC
#include<iostream>
/*****************************************************
3D Model Viewer
v3.0
Authors: Caleb Latimer, Daniel Warrick

This program is designed to read a .obj file into 2
vectors, then render the vertices in a 3D context.
After rendering, key listeners are implemented to
control simulated transformations by adjusting the
camera position. The color of the vertices can also
be adjusted through similar key listeners that affect
RGB values.

*****************************************************/

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include"GL/freeglut_std.h" 
#include<vector>
#include<fstream>
#include<string>
#include"objLoader.h"
using namespace std;
//contains the majority of the enable functions
void init(GLvoid);
//defines key listeners
void keyPressed(unsigned char key, int x, int y);
//global variables which are used to alter camera
//position through gluLookAt()
int camX, camY, camZ;
//global variables which are used to alter the color
//of the rendered vertices
GLint red, blue, green;
//main object declaration
Loader obj1;
int main(int argc, char *argv[]) {
	init();
	// clarify obj file 
	obj1.loadObject(); // calls load function()
	glutInit(&argc, argv);
	//depth, doubleBuffering and color
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//create window for opengl context
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("3d Model");
	//draw image
	obj1.render();
	//reads keyboard inputs
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}
void init(GLvoid) // Create Some Everyday Functions
{

	glShadeModel(GL_FLAT);	// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	// White Background
	glClearDepth(1.0f);	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
/*
*KeyListeners:
*'w'/'s': increase/decrease z coordinate of camera position
*'a'/'d': increase/decrease x coordinate of camera position
*'q'/'e': increase/decrease y coordinate of camera position
*'u'/'j': increase/decrease R value of RGB
*'i'/'k': increase/decrease G value of RGB
*'o'/'l': increase/decrease B value of RGB
*
* After each adjustment is made, the image is cleared and
* redrawn through a call to render()
*/
void keyPressed(unsigned char key, int x, int y) {
	if (key == 'w') {
		camZ += 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}

	if (key == 's') {
		camZ -= 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'a') {
		camX -= 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'd') {
		camX += 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'q') {
		camY -= 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'e') {
		camY += 10;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'r') {
		glRotatef(10, 0.f, 1.f, 0.f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	//color changing
	if (key == 'u') {
		red += 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'j') {
		red -= 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'i') {
		green += 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'k') {
		green -= 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'o') {
		blue += 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}
	if (key == 'l') {
		blue -= 3;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj1.render();
	}

}
