#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define DEG_TO_RAD(X) (X * M_PI / 180.0)

double ray(double degAngle, double posx, double posy) {
    double angle = DEG_TO_RAD(degAngle);
    double AdjY = posy - floor(posy);
    double rayTestA = AdjY / cos(angle);
    double AdjX = ceil(posx) - posx;
    double rayTestB = AdjX / cos((DEG_TO_RAD(90))-angle);
    if(fabs(rayTestB) < fabs(rayTestA)) {
        return fabs(rayTestB);
    }
    else {
        return fabs(rayTestA);
    }
}

void drawRect(double width, double height, double x) {
    double topY = height/2;
    double shadeColour = topY;
    if (topY > 1) {
        shadeColour = 1;
    }
    glColor3f(shadeColour,shadeColour,shadeColour);
    double topX = width+x;
    glBegin(GL_TRIANGLES);
        glVertex3f(topX,topY, -5.0);
        glVertex3f(x,-1*topY, -5.0);
        glVertex3f(topX,-1*topY, -5.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(topX, topY, -5.0);
        glVertex3f(x, topY, -5.0);
        glVertex3f(x, -1*topY, -5.0);
}