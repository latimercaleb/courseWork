#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<GL/glut.h>
//allows use of camera position and color variables
// in loader.cpp
extern int camX, camY, camZ, red, blue, green;
using namespace std;

class Loader {
public:
	Loader();
	void loadObject();
	void render();
protected:

private:
	char vertexType;
	vector<float> vertices;
	vector<float> faces;
	GLfloat vX, vY, vZ, fX, fY, fZ;
	GLint coordinateCtr, faceCoordinateCtr;

};