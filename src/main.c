#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RAD_TO_DEG(X) (X * 180.0 / M_PI)
#define DEG_TO_RAD(X) (X * M_PI / 180.0)

int x,y,xo,yo; //X, Y, X offset, Y offset
int fov = 20; //FOV in degrees
double viewAngle = 20; // View angle relative to straight up (0 degrees)
int mapX, mapY;
int mapS = 16;
int map[4][4] = {
	{1,1,1,1},
	{1,0,0,1},
	{1,0,0,1},
	{1,1,1,1},
};

double ray2d(double angle) {
	double angle	
	double distance = 1.00;
	if (angle >= 0 && angle <= 90) {
		printf("northeast\n");
	} else if (angle >= 90 && angle <= 180) {
		printf("southeast\n");
	} else if (angle >= 180 && angle <= 270) {
		printf("southwest\n");
	} else if (angle >= 270) {
		printf("northwest\n");
	}
	



	return distance;
}

int main() {
	return 0;
}
