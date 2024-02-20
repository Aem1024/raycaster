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

double ray2d(double angle, double x, double y) {
	double xo = floor(x) + 1; //TODO make this equal to the nearest 16th of a unit 
	int quadDir; // 1 Northeast, 2 Southeast, 3 Southwest, 4 Northwest	
	double distance = 1.00;
	if (angle >= 0 && angle <= 90) {
		printf("northeast\n");
		quadDir = 1;
	} else if (angle >= 90 && angle <= 180) {
		printf("southeast\n");
		quadDir = 2;
	} else if (angle >= 180 && angle <= 270) {
		printf("southwest\n");
		quadDir = 3;
	} else if (angle >= 270) {
		printf("northwest\n");
		quadDir = 4;
	}
	double relAngle; // Angle from nearest quad counter-clockwise 
	relAngle = quadDir * 90 - angle; //i think this finds the angle between the nearest quad
	
	// TODO Ray math	
	printf("%lf\n",relAngle);
	printf("%lf\n", xo);
	printf("%lf\n", x);
	return distance;
}

int main() {
	ray2d(110, 1.10, 1.10);
	return 0;
}
