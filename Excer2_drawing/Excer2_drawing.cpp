#include <GL/glut.h>
#include <stdlib.h>

#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0, 0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0B0000000100000001);  /*  dotted  */
    drawOneLine(50.0, 125.0, 150.0, 125.0);
    glLineStipple(1, 0B0000000011111111);  /*  dashed  */
    drawOneLine(150.0, 125.0, 250.0, 125.0);
    glLineStipple(1, 0B0001110001000111);  /*  dash/dot/dash  */
    drawOneLine(250.0, 125.0, 350.0, 125.0);
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* 规定二维视景区域，参数分别为left,right,bottom,top  */
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
