// buildingPrcedure.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <GL\glut.h>

GLsizei winWidth = 0, winHeight = 0;

GLfloat colorPalette[4][3] = { { 0,1,0 },{ 0,0,1 },{ 1,0,0 },{ 1, 1, 1 } };
GLfloat colorPalette1[4][3] = { { 1, .894, .455 },{ .749, .533, .235 },{ .529, .302, .09 },{ .341, .133, 0 } };
GLfloat colorPalette2[4][3] = { { .129, .451, .157 },{ .318, .651, .161 },{ .502, .851, .255 },{ .349, .231, .008 } };
GLfloat colorPalette3[4][3] = { { .18, .067, .176 },{ .329, 0, .196 },{ .51, .012, .2 },{ .788, .157, .243 } };
GLfloat colorPalette4[4][3] = { { .482, .165, .231 },{ .898, .463, .38 },{ .973, .773, .549 },{ .973, .906, .635 } };
GLfloat colorPalette5[4][3] = { { .192, .584, .537 },{ .204, .302, .424 },{ .216, .149, .314 },{ .243, .106, .235 } };
GLfloat colorPalette6[4][3] = { { .047, .702, .91 },{ 0, 1, .925 },{ .047, .91, .553 },{ .071, 1, .306 } };
GLfloat colorPalette7[4][3] = { { 1, .561, .255 },{ .91, .392, .235 },{ 1, .349, .306 },{ .91, .235, .984 } };
GLfloat colorPalette8[4][3] = { { .902, .902, .902 },{ 1, .702, .702 },{ .129, .651, .553 },{ .086, .569, .522 } };
GLfloat colorPalette9[4][3] = { { .039, .8, .792 },{ .149, 1, .51 },{ 1, .4, .553 },{ .8, .039, .612 } };
GLfloat colorPalette10[4][3] = { { .011,.153,.353 },{ .102, .49, .843 },{ .949, .722, .035 },{ .953, .455, .008 } };

GLfloat houseWidth, houseHeight;
GLfloat windowWidth = 50;
GLfloat windowHeight = 50;
GLfloat doorWidth = 50;
GLfloat spin_y = 0;
GLfloat spin_x = 0;
GLfloat old_x = 0;
GLfloat old_y = 0;
GLfloat floorWidths[1000];
GLfloat mid, houseX, houseY, startX, startY, numWindowsW, numFloors, maxFloorHeight, windowGapW, windowGapH, numDoors, doorGap, doorX, doorY ,sideX;

GLfloat roofWidth = 100;
GLfloat roofHeight = 2000;
GLfloat randomNumber;

void reshape(int x, int y);
void display(void);
void mouse(int btn, int state, int x, int y);
void drawHouse();
void chooseColor(void);
void drawCube(int level);
float genRand();
void calculateWidth(float houseWidth);
void calculateHeight();
void mouseMotion(int x, int y);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Procedural Modeling of House");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	winWidth = glutGet(GLUT_WINDOW_WIDTH);
	winHeight = glutGet(GLUT_WINDOW_HEIGHT);

	randomNumber = genRand();
	calculateWidth(randomNumber);
	randomNumber = genRand();
	calculateHeight();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
    return 0;
}


void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3000, 3000, 3000, -3000, -2000.0, 2000.0);
	gluLookAt(0, 0, 5, 0,0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawHouse();
	glFlush();
}

void mouse(int btn, int state, int x, int y) {
	//Set the location of the click
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		old_x = x;
		old_y = y;
	}
	
	//Sets size and color
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

		randomNumber = genRand();
		calculateWidth(randomNumber);
		randomNumber = genRand();
		calculateHeight();

		chooseColor();
		glutPostRedisplay();
	}
}

void mouseMotion(int x, int y)
{
	spin_x = x - old_x;
	spin_y = y - old_y;

	glutPostRedisplay();
}

//Calculates the height of the building and sets the width of each floor
void calculateHeight() {
	houseHeight = genRand();
	numFloors = (GLint)(houseHeight / 100);
	windowGapH = (houseHeight - (numFloors * windowHeight)) / (numFloors + 1);
	maxFloorHeight = houseHeight / numFloors;
	
	for (int i = 1; i <= numFloors; i++) {
		floorWidths[i] = genRand();
	}

/*
	for (int i = 1; i <= numFloors; i++) {
		for (int j = i + 1; j <= numFloors; j++) {
			if (floorWidths[i] < floorWidths[j]) {
				float temp = floorWidths[i];
				floorWidths[i] = floorWidths[j];
				floorWidths[j] = temp;
			}
		}
	}
	*/
}

//Generates a random number
float genRand() {
	float MIN_RAND = 200;
	float MAX_RAND = 6000;
	float range = MAX_RAND - MIN_RAND;
	float randomNumber;
	return randomNumber = range * ((((float)rand()) / (float)RAND_MAX)) + MIN_RAND;
}

//Caculates the information of each floor based on the width of the floor
void calculateWidth(float houseWidth) {
	numWindowsW = (GLint)houseWidth / 100;
	numDoors = (GLint)houseWidth / 200;
	windowGapW = (houseWidth - (numWindowsW * windowWidth)) / (numWindowsW + 1);
	doorGap = (houseWidth - (numDoors * doorWidth)) / (numDoors + 1);
	mid = houseWidth / 2;
	houseX = mid;
}

void drawHouse() {
	//For rotating the building
	glRotatef(-spin_y, 1, 0, 0);
	glRotatef(spin_x, 0, 1, 0);

	calculateWidth(floorWidths[1]);
	houseWidth = floorWidths[1];
	//Roof
	glColor3fv(colorPalette[1]);
	glBegin(GL_POLYGON);
	glVertex3f(-houseX - roofWidth / 2, -houseY, -mid - roofWidth / 2);
	glVertex3f(-houseX + houseWidth + roofWidth / 2, -houseY, -mid - roofWidth / 2);
	glVertex3f(-houseX + houseWidth / 2, -houseY - roofHeight, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-houseX + houseWidth + roofWidth / 2, -houseY, -mid - roofWidth / 2);
	glVertex3f(-houseX + houseWidth + roofWidth / 2, -houseY, mid + roofWidth / 2);
	glVertex3f(-houseX + houseWidth / 2, -houseY - roofHeight, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-houseX - roofWidth / 2, -houseY, mid + roofWidth / 2);
	glVertex3f(-houseX + houseWidth + roofWidth / 2, -houseY, mid + roofWidth / 2);
	glVertex3f(-houseX + houseWidth / 2, -houseY - roofHeight, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-houseX - roofWidth / 2, -houseY, mid + roofWidth / 2);
	glVertex3f(-houseX - roofWidth / 2, -houseY, -mid - roofWidth / 2);
	glVertex3f(-houseX + houseWidth / 2, -houseY - roofHeight, 0);
	glEnd();

	//Draws a cube for each floor in the building
	for (int i = 1; i <= numFloors; i++) {
		calculateWidth(floorWidths[i]);
		drawCube(i);
		
		houseY -= maxFloorHeight;
	}
	houseY = houseHeight/2;
}

void drawCube(int level) {
	//If not the bottome level draw the windows
	if (level != numFloors) {
		startX = -houseX;
		startY = -houseY;
		sideX = -mid;
		for (int j = 1; j <= numWindowsW; j++) {
			//Back windows
			glColor3fv(colorPalette[2]);
			glBegin(GL_POLYGON);
			glVertex3f(startX + windowGapW, startY + windowGapH, -mid - .1);
			glVertex3f(startX + windowGapW + windowWidth, startY + windowGapH, -mid - .1);
			glVertex3f(startX + windowGapW + windowWidth, startY + windowGapH + windowHeight, -mid - .1);
			glVertex3f(startX + windowGapW, startY + windowGapH + windowHeight, -mid - .1);
			glEnd();

			//Front windows
			glBegin(GL_POLYGON);
			glVertex3f(startX + windowGapW, startY + windowGapH, mid + .1);
			glVertex3f(startX + windowGapW + windowWidth, startY + windowGapH, mid + .1);
			glVertex3f(startX + windowGapW + windowWidth, startY + windowGapH + windowHeight, mid + .1);
			glVertex3f(startX + windowGapW, startY + windowGapH + windowHeight, mid + .1);
			glEnd();

			//Right windows
			glBegin(GL_POLYGON);
			glVertex3f(floorWidths[level] / 2 + .1, startY + windowGapH, sideX + windowGapW);
			glVertex3f(floorWidths[level] / 2 + .1, startY + windowGapH, sideX + windowGapW + windowWidth);
			glVertex3f(floorWidths[level] / 2 + .1, startY + windowGapH + windowHeight, sideX + windowGapW + windowWidth);
			glVertex3f(floorWidths[level] / 2 + .1, startY + windowGapH + windowHeight, sideX + windowGapW);
	    	glEnd();

			//Left windows
			glBegin(GL_POLYGON);
			glVertex3f(-floorWidths[level] / 2 - .1, startY + windowGapH, sideX + windowGapW);
			glVertex3f(-floorWidths[level] / 2 - .1, startY + windowGapH, sideX + windowGapW + windowWidth);
			glVertex3f(-floorWidths[level] / 2 - .1, startY + windowGapH + windowHeight, sideX + windowGapW + windowWidth);
			glVertex3f(-floorWidths[level] / 2 - .1, startY + windowGapH + windowHeight, sideX + windowGapW);
			glEnd();

			startX = startX + (windowGapW)+windowWidth;
			sideX = sideX + windowGapW + windowWidth;
		}
	}
	//IF on the last floor draw the doors
	else {
		doorX = -houseX;
		doorY = -houseY;
		sideX = -mid;
		for (int d = 1; d <= numDoors; d++) {
			glColor3fv(colorPalette[3]);

			//Front door
			glBegin(GL_POLYGON);
			glVertex3f(doorX + doorGap, doorY + maxFloorHeight - 90, mid + .01);
			glVertex3f(doorX + doorGap + doorWidth, doorY + maxFloorHeight - 90, mid + .01);
			glVertex3f(doorX + doorGap + doorWidth, doorY + maxFloorHeight, mid + .01);
			glVertex3f(doorX + doorGap, doorY + maxFloorHeight, mid + .01);
			glEnd();

			//Back door
			glBegin(GL_POLYGON);
			glVertex3f(doorX + doorGap, doorY + maxFloorHeight - 90, -mid - .01);
			glVertex3f(doorX + doorGap + doorWidth, doorY + maxFloorHeight - 90, -mid - .01);
			glVertex3f(doorX + doorGap + doorWidth, doorY + maxFloorHeight, -mid - .01);
			glVertex3f(doorX + doorGap, doorY + maxFloorHeight, -mid - .01);
			glEnd();

			//Left door
			glBegin(GL_POLYGON);
			glVertex3f(-floorWidths[level] / 2 - .1, doorY + maxFloorHeight - 90, sideX + doorGap);
			glVertex3f(-floorWidths[level] / 2 - .1, doorY + maxFloorHeight - 90, sideX + doorGap + doorWidth);
			glVertex3f(-floorWidths[level] / 2 - .1, doorY + maxFloorHeight, sideX + doorGap + doorWidth);
			glVertex3f(-floorWidths[level] / 2 - .1, doorY + maxFloorHeight, sideX + doorGap);
			glEnd();

			//Right door
			glBegin(GL_POLYGON);
			glVertex3f(floorWidths[level] / 2 + .1, doorY + maxFloorHeight - 90, sideX + doorGap);
			glVertex3f(floorWidths[level] / 2 + .1, doorY + maxFloorHeight - 90, sideX + doorGap + doorWidth);
			glVertex3f(floorWidths[level] / 2 + .1, doorY + maxFloorHeight, sideX + doorGap + doorWidth);
			glVertex3f(floorWidths[level] / 2 + .1, doorY + maxFloorHeight, sideX + doorGap);
			glEnd();

			doorX = doorX + (doorGap) + doorWidth;
			sideX = sideX + (doorGap) + doorWidth;
		}
	}
	
	glColor3fv(colorPalette[0]);
	//Draws back wall
	glBegin(GL_POLYGON);
	glVertex3f(-houseX, -houseY, -mid); //0
	glVertex3f(houseX, -houseY, -mid);//1
	glVertex3f(houseX, -houseY + maxFloorHeight, -mid); //2
	glVertex3f(-houseX, -houseY + maxFloorHeight, -mid); //3
	glEnd();

	//Draws right wall
	glBegin(GL_POLYGON);
	glVertex3f(houseX, -houseY, -mid); //1
	glVertex3f(houseX, -houseY, mid); //5
	glVertex3f(houseX, -houseY + maxFloorHeight, mid); //7
	glVertex3f(houseX, -houseY + maxFloorHeight, -mid); //2
	glEnd();

	//Draws front wall
	glBegin(GL_POLYGON);
	glVertex3f(-houseX, -houseY, mid); //4
	glVertex3f(houseX, -houseY, mid); //5
	glVertex3f(houseX, -houseY + maxFloorHeight, mid); //7
	glVertex3f(-houseX, -houseY + maxFloorHeight, mid); //6
	glEnd();

	//Draws left wall
	glBegin(GL_POLYGON);
	glVertex3f(-houseX, -houseY, -mid); //0
	glVertex3f(-houseX, -houseY + maxFloorHeight, -mid); //2
	glVertex3f(-houseX, -houseY + maxFloorHeight, mid); // 6
	glVertex3f(-houseX, -houseY, mid); //4
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(houseX, -houseY + maxFloorHeight, -mid); //2
	glVertex3f(-houseX, -houseY + maxFloorHeight, -mid); //3
	glVertex3f(-houseX, -houseY + maxFloorHeight, mid); //6
	glVertex3f(houseX, -houseY + maxFloorHeight, mid); //7
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-houseX, -houseY, -mid); //0
	glVertex3f(houseX, -houseY, -mid); //1
	glVertex3f(houseX, -houseY, mid); //5
	glVertex3f(-houseX, -houseY, mid); //4
	glEnd();
}

void chooseColor(void) {

	float MIN_RAND1 = 1;
	float MAX_RAND1 = 10;
	float range1;
	int randomNumber1;
	range1 = MAX_RAND1 - MIN_RAND1;
	randomNumber1 = range1 * ((((float)rand()) / (float)RAND_MAX)) + MIN_RAND1;

	if (randomNumber1 == 1)
		memcpy(colorPalette, colorPalette1, sizeof(colorPalette));
	else if (randomNumber1 == 2)
		memcpy(colorPalette, colorPalette2, sizeof(colorPalette));
	else if (randomNumber1 == 3)
		memcpy(colorPalette, colorPalette3, sizeof(colorPalette));
	else if (randomNumber1 == 4)
		memcpy(colorPalette, colorPalette4, sizeof(colorPalette));
	else if (randomNumber1 == 5)
		memcpy(colorPalette, colorPalette5, sizeof(colorPalette));
	else if (randomNumber1 == 6)
		memcpy(colorPalette, colorPalette6, sizeof(colorPalette));
	else if (randomNumber1 == 7)
		memcpy(colorPalette, colorPalette7, sizeof(colorPalette));
	else if (randomNumber1 == 8)
		memcpy(colorPalette, colorPalette8, sizeof(colorPalette));
	else if (randomNumber1 == 9)
		memcpy(colorPalette, colorPalette9, sizeof(colorPalette));
	else
		memcpy(colorPalette, colorPalette10, sizeof(colorPalette));
}

