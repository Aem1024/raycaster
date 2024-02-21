#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUBUNITS 16
#define FOV 20
#define RAD_TO_DEG(X) (X * 180.0 / M_PI)
#define DEG_TO_RAD(X) (X * M_PI / 180.0)
// 
//TODO Add movement, tie to delta time
double x, y;; //X and Y coordinates
double viewAngle = 20; // View angle relative to straight up (0 degrees)
int mapX, mapY;
int map[4][4] = {
	{1,1,1,1},
	{1,0,0,1},
	{1,0,0,1},
	{1,1,1,1},
};
double findSubUnit(double x) { // Find subunit of coordinate from bottom left
	double xpart, xfract;
	xfract = modf(x, &xpart);
	double xo = xfract * SUBUNITS;
	xo = round(xo);
	return xo;
}
double ray2d(double angle, double x, double y) {
	double xo = findSubUnit(x);
	int quadDir; // 1, NE, 2, SE, 3, SW, 4, NW
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
	double farClockAngle = 90 - relAngle;
	double angle1 = 90 - relAngle;
	
	// TODO Ray math	
	double horTri1, vertTri1, hypo; 
	 

	printf("%lf\n",relAngle); // Prints relative angle, x offset, and x coord.
	printf("%lf\n", xo);
	printf("%lf\n", x);
	return distance;
}
int main() {
	ray2d(110, 1.5, 1.10);
	return 0;
}
