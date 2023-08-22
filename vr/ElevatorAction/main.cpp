#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include "glut\glut.h"
#include "main.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "Elevator.hpp"
#include "DocumentDoor.hpp"
#include "ExtraLife.hpp"
#include "Levels.hpp"

using namespace std;

Game game = Game(generate_levels);

const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

int glutTime = -1;
int getDelta(void) {
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int delta = newTime;
	if (glutTime != -1) {
		delta -= glutTime;
	}
	glutTime = newTime;
	return delta;
}

float getDeltaTime(void) {
	return getDelta() / 1000.0f;
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	game.keyboard_press(key, x, y);
}

void myKeyboardUpFunc(unsigned char key, int x, int y)
{
	game.keyboard_release(key, x, y);
}

void mySpecialKeyFunc(int key, int x, int y)
{
	game.specialkey_press(key, x, y);
}

void mySpecialUpFunc(int key, int x, int y)
{
	game.specialkey_release(key, x, y);
}


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	float delta = getDeltaTime();

	game.process(delta);
	game.render(delta);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void initRendering()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport(0, 0, w, h);

	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin)*scale;
		windowXmax = center + (Xmax - center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin)*scale;
		windowYmax = center + (Ymax - center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);

}

void initialize() {
	srand(time(0));
}

void generate_levels(Game *game) {
	game->add_level(Levels::level1());
	game->add_level(Levels::level2());
	game->add_level(Levels::level3());
}

int main(int argc, char** argv)
{
	initialize();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Elevator Action");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	glutSpecialFunc(mySpecialKeyFunc);
	glutSpecialUpFunc(mySpecialUpFunc);


	glutReshapeFunc(resizeWindow);

	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}
