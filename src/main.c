#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
#endif
#include "ray.h"

#define RAD_TO_DEG(X) ((X) * 180.0 / M_PI)
#define DEG_TO_RAD(X) ((X) * M_PI / 180.0)

#define WIDTH 1280
#define HEIGHT 500


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}



int map[4][4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
};
double x = 1.5;
double y = 1.5;
float deltaMove = 0;
float movespeed = 0.5;
float angle = 45;


float deltaAngle = 0.0f;
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	if (key == 'q') {
	y += sin(DEG_TO_RAD(angle)) * deltaMove;
	x -= cos(DEG_TO_RAD(angle)) * deltaMove;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case 'a' : deltaAngle = -0.5; break;
		case 'd' : deltaAngle = 0.5; break;
		case 'w' : deltaMove = 0.01f; break;
		case 's' : deltaMove = -0.01f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case 'a' :
		case 'd' : deltaAngle = 0.0f;break;
		case 'w' :
		case 's' : deltaMove = 0; break;
	}
}
void computeAngle(float deltaAngle) {
	angle += deltaAngle;
	if (angle < 0) {
		angle = 360 + angle;
	}
	else if (angle > 360) {
        angle = angle - 360;
    }
}
void computePos(float deltaMove) {
	x += sin(DEG_TO_RAD(angle)) * deltaMove;
	y -= cos(DEG_TO_RAD(angle)) * deltaMove;

	//printf("X: %lf, Y: %lf    Angle: %lf\nX: %lf, Y: %lf\n\n", xc, yc, angle,x,y);
}
void myDraw(void) {
	if (isnan(y)) {
		printf("NaN!\n");
		y = 1.5;
	}
    if(deltaAngle) {
    	computeAngle(deltaAngle);
		
    }
	if (deltaMove) {
		computePos(deltaMove);
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    // Ray height
    float rayY = ray(angle, x, y)/2;
    // Horizontal resolution of each "Bar"
    float vertWidth = 0.1;
    // Bottom left corner of our "Bar"
    float xloc;
	glColor3f(0.25,0,0.25);
	drawRect(10, 2, -5, -2);
	glColor3f(0.30, 0.686, 0.97);
	drawRect(10,2,-5,0);
    for(int i = -31; i < 31; i++) {
        // The angle we're finding the ray from
        int calcAngle = angle+i;
        // Our x location
        xloc = (i)*vertWidth;
        // our height is the reciprocal of our distance
        rayY = (1/ray(calcAngle, x, y))/cos(DEG_TO_RAD(calcAngle)-DEG_TO_RAD(angle));
        //Draw the rectangle
        drawWall(vertWidth, rayY, xloc);
    }
    
	glEnd();

	glutSwapBuffers();
}




int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(749,500);
    glutCreateWindow("Elli torture simulator 2020");
    
    // register callbacks
	glutDisplayFunc(myDraw);
	glutReshapeFunc(changeSize);
	glutIdleFunc(myDraw);
	glutSpecialFunc(pressKey);

	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	printf("%lf\n",ray(30, 0.5, 0.5) );
	printf("%lf\n\n",ray(120,0.5,0.5));

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
