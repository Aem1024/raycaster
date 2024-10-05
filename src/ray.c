
#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#define DEG_TO_RAD(X) ((X) * M_PI / 180.0)


double ray2d(double angle, float x , float y) {
    double rayTestA = y / cos(angle);
    double rayTestB = x / cos((DEG_TO_RAD(90))-angle);
    if (fabs(rayTestB) < fabs(rayTestA)) {return fabs(rayTestB);}
    else {return fabs(rayTestA);}
}

double ray(double degAngle, double posx, double posy) {
    double angle = degAngle;
    double AdjX;
    double AdjY;
    if (angle < 0) {
        angle += 360;
    }
    angle = fmod(angle, 360);
    switch((int) angle) {
        case (0):
        case (360):
            return posy - floor(posy);break;
        case 90:
            return ceil(posx) - posx;break;
        case 180:
            return ceil(posy)-posy;break;
        case 270:
            return posx - floor(posx);break;

    }
    printf("%lf\n", angle);
    if ((angle > 0) && (angle < 90)) {
        angle = DEG_TO_RAD(angle);
        AdjY = posy - floor(posy);
        AdjX = ceil(posx) - posx;
        printf("0-90 Y: %lf   X: %lf\n\n", AdjY, AdjX);
        printf("Angle: %lf\n\n", angle);
        return ray2d(angle, AdjX, AdjY);
    }
    
    else if ((angle > 90) && (angle < 180)) {
        angle = DEG_TO_RAD(angle-90);
        AdjY = ceil(posx) - posx;
        AdjX = ceil(posy)-posy;
        printf("90-180 Y: %lf   X: %lf\n", AdjY, AdjX);
        printf("Angle: %lf\n\n", angle);
        return ray2d(angle, AdjX, AdjY);
    } 

    else if ((angle >180) && (angle < 270)) {
        angle = DEG_TO_RAD(angle-180);
        AdjY = ceil(posy)-posy;
        AdjX = posx - floor(posx);
        printf("180-270 Y: %lf   X: %lf\n\n", AdjY, AdjX);
        printf("Angle: %lf\n\n", angle);
        return ray2d(angle, AdjX, AdjY);
    }

    else if ((angle > 270) && (angle < 360)) {
        angle = DEG_TO_RAD(angle-270);
        AdjY = posx - floor(posx);
        AdjX = posy-floor(posy);
        printf("270-360 Y: %lf   X: %lf\n\n", AdjY, AdjX);
        printf("Angle: %lf\n\n", angle);
        return ray2d(angle, AdjX, AdjY);
    }
    else {printf("idk\n");return 100;}
}

void drawRect(double width, double height, double x) {
    double topY = height/2;
    double shadeColour = topY*0.5;
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
