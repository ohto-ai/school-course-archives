#include <GL/glut.h>
#include <stdlib.h>
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Red
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(-2.0f, -1.0f, 0.0f);
	glEnd();
	// Blue
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, -2.0f, 0.0f);
	glVertex3f(-1.0f, -2.0f, 0.0f);
	glEnd();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
	glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 10.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glEnable(GL_DEPTH_TEST) ;//∆Ù”√…Ó∂»≤‚ ‘ 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
