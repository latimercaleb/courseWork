#include<iostream>
#include"objLoader.h"

using namespace std;
/*
* Constructor:
* initializes vertex counters and assigns initial
* camera position/vertex color
*/
Loader::Loader() {
	coordinateCtr = 0;
	faceCoordinateCtr = 0;

	camX = 0; camY = 0; camZ = -350;
	red = 1; blue = 0; green = 0;
}
/*
*Reads .obj file into vectors: "vertices" and "faces"
*/
void Loader::loadObject() {
	//declare ifstream
	ifstream objFile;
	//open .obj file
	objFile.open("buddha_30k.obj");
	//test that file has been opened
	if (!objFile)
		cout << "Error: File Not Found" << endl;


	//read first character of each line; this determines
	//whether the following data points belong in vertices
	//or faces (vectors)
	objFile >> vertexType;
	//read data until end of file
	while (!objFile.eof()) {

		if (vertexType == 'v') {

			//Uses variables for temporary storage and inserts
			//their values into the vector
			objFile >> vX >> vY >> vZ;
			vertices.push_back(vX);
			coordinateCtr++;

			vertices.push_back(vY);
			coordinateCtr++;

			vertices.push_back(vZ);
			coordinateCtr++;
			//get's first character of the next line
			objFile >> vertexType;
		}

		else if (vertexType == 'f') {
			//Uses variables for temporary storage and inserts
			//their values into the vector
			objFile >> fX >> fY >> fZ;

			faces.push_back(fX);
			faceCoordinateCtr++;

			faces.push_back(fY);
			faceCoordinateCtr++;

			faces.push_back(fZ);
			faceCoordinateCtr++;
			//get's first character of the next line
			objFile >> vertexType;
		}
		else {
			objFile >> vertexType;
		}
	}
	//close file after all data has been extracted
	objFile.close();
}
/*
* Sets the perspective, sets the camera position
* and draws the vertices from the declared vectors
*/
void Loader::render(void) {
	//reset counter values each time render is called
	coordinateCtr = 0;
	faceCoordinateCtr = 0;

	//necessary for perspective manipulation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//controls viewing pane
	gluPerspective(45, 1, 0, 50);
	//controls camera position
	gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);


	//Draws all vertices stored in the vectors
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	for (; coordinateCtr<vertices.size(); coordinateCtr += 9) {

		glBegin(GL_POINTS);
		glVertex3f(vertices[coordinateCtr], vertices[coordinateCtr + 1], vertices[coordinateCtr + 2]);
		glVertex3f(vertices[coordinateCtr + 3], vertices[coordinateCtr + 4], vertices[coordinateCtr + 5]);
		glVertex3f(vertices[coordinateCtr + 6], vertices[coordinateCtr + 7], vertices[coordinateCtr + 8]);
		glColor3f(red, green, blue);
		glEnd();

		//Draws faces and associates them with existing vertices
		//***Not currently functioning
		/*glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(faces[faceCoordinateCtr], faces[faceCoordinateCtr+1], faces[faceCoordinateCtr+2]);
		glVertex3f(faces[faceCoordinateCtr+3], faces[faceCoordinateCtr+4], faces[faceCoordinateCtr+5]);
		glVertex3f(faces[faceCoordinateCtr+6], faces[faceCoordinateCtr+7], faces[faceCoordinateCtr+8]);
		glPopMatrix;
		glEnd();
		faceCoordinateCtr+=9;*/
	}


	glutSwapBuffers();
}
