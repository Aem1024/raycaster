#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUBUNITS 16
#define FOV 20
#define RAD_TO_DEG(X) (X * 180.0 / M_PI)
#define DEG_TO_RAD(X) (X * M_PI / 180.0)
#define MAPX 4
#define MAPY 4


//TODO Add movement, tie to delta time
double x, y;; //X and Y coordinates
double viewAngle = 44; // View angle relative to straight up (0 degrees)
int map[MAPX][MAPY] = {
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

double ray2d(double angle, double x, double y, int map[MAPX][MAPY]) {
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
	int checkHor, checkVert;	
	// TODO Ray math	
	double horTri1, vertTri1, hypo; 
	
	// Find horizontal length
	horTri1 = modf(x, &horTri1);
	horTri1 = 1 - horTri1;	
	
	// Find vertical length
	vertTri1 = modf(y, &vertTri1);
	vertTri1 = 1 - vertTri1;
	
	if (angle == 90 || angle == 270) {
		checkHor = 0;
	}
	if (angle == 0 || angle == 180) {
		checkVert = 0;
	}
	double horOrVert; //Just to test something
	double VorH; //check if ray passes throuh hor or vert, 1 = hor, 0 = vert
	// Test if ray passes through horizontal or vertical first
	horOrVert = tan(DEG_TO_RAD(angle) * horTri1);	
	if (angle > 90 && angle < 270) {
		if (vertTri1 <= horOrVert) {
			int a;
			//TODO impletment angles that go down
		}
	
	} else {
		if (vertTri1 >= horOrVert) {
			VorH = 1;
		} else {
			VorH = 0;
		}
	}
	int mapX = round(x);
	int mapY = round(y);	
	printf("%d\n", map[mapX][mapY]);
	double xfract, yfract;
	double Hadj = 1 - modf(y, &yfract);
	double Hopp =  tan(DEG_TO_RAD(relAngle)) * Hadj;
	double Hdistance; //Distance to nearest horizontal
	Hdistance = pow(Hadj, 2) + pow(Hopp, 2);
	Hdistance = sqrt(Hdistance);
	return Hdistance;
		
}
int main() {
	double distance = ray2d(viewAngle, 1.5, 1.1, map);
	printf("%lf\n", distance);
	return 0;
}
