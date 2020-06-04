#include <GL/glut.h>
#include <stdlib.h>
float x1 = -0.25, y1 = -0.25;//
float width = 0.5, height = 0.5;
float xMin = -1, xMax = 1;
float yMin = -1, yMax = 1;
float widthWindows = 400, heightWindows = 400;
float colorR = 0.5, colorG = 0.5, colorB = 0.5;
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//绘制一个矩形，z轴位置为-1.0f
	glColor3f(colorR, colorG, colorB);
	glRectf(x1, y1, x1 + width, y1 + height);
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* 规定二维视景区域，参数分别为left,right,bottom,top  */
	glOrtho(xMin, xMax, yMin, yMax, 0.0, 10.0);
}
void MyMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			colorR += 0.1;
			if (colorR > 1.0)
				colorR = 0.0;
			glutPostRedisplay();
			break;
		case GLUT_MIDDLE_BUTTON:
			colorG += 0.1;
			if (colorG > 1.0)
				colorG = 0.0;
			glutPostRedisplay();
			break;
		case GLUT_RIGHT_BUTTON:
			colorB += 0.1;
			if (colorB > 1.0)
				colorB = 0.0;
			glutPostRedisplay();
			break;
		}
	}
}
void MyMotion(int x, int y)
{
	x1 = (float)x / widthWindows * (xMax - xMin) + xMin - width / 2;
	y1 = (float)(heightWindows - y) / heightWindows * (yMax - yMin) + yMin - width / 2;
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':// 矩形坐标变量修改使得矩形上移
		y1 += 0.1;
		if (y1 >= yMax - height)
			y1 = yMax - height;
		glutPostRedisplay();
		break;
	case 'S':
	case 's': // 矩形坐标变量修改使得矩形下移
		y1 -= 0.1;
		if (y1 <= yMin)
			y1 = yMin;
		glutPostRedisplay();
		break;
	case 'A':
	case 'a': // 矩形坐标变量修改使得矩形左移
		x1 -= 0.1;
		if (x1 <= xMin)
			x1 = xMin;
		glutPostRedisplay();
		break;
	case 'D':
	case 'd': // 矩形坐标变量修改使得矩形右移
		x1 += 0.1;
		if (x1 >= xMax - width)
			x1 = xMax - width;
		glutPostRedisplay();
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);
	glutMotionFunc(MyMotion);
	glutMainLoop();
	return 0;
}
