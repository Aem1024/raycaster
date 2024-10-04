#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "ray.h"

#define RAD_TO_DEG(X) (X * 180.0 / M_PI)
#define DEG_TO_RAD(X) (X * M_PI / 180.0)

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

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
double posX = 1.5;
double posY = 1.5;
int angle = 45;



void myDraw(void) {

    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Ray height
    double rayY = ray(angle, posX, posY)/2;
    // Horizontal resolution of each "Bar"
    double vertWidth = 0.05;
    // Bottom left corner of our "Bar"
    double xloc;
    for(int i = -30; i < 31; i++) {
        // The angle we're finding the ray from
        int calcAngle = angle+i;
        // Our x location
        xloc = (i)*vertWidth;
        // our height is the reciprocal of our distance
        rayY = 1/ray(calcAngle, posX, posY);
        //Draw the rectangle
        drawRect(vertWidth, rayY, xloc);
    }
    
	glEnd();

	glutSwapBuffers();
}




int main(int argc, char** argv) {
    // Initialize GLUT
    printf("%lf\n", ray(angle, posX, posY));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280,500);
    glutCreateWindow("<3");
    
    // Display function
    glutDisplayFunc(myDraw);
    glutReshapeFunc(changeSize);


    // Check keyboard input
    glutKeyboardFunc(processNormalKeys);


    // Open main loop
    glutMainLoop();
    
    return 1;
}