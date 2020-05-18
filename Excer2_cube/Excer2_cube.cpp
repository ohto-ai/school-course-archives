#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();             /* 设置单位阵 */
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /* 设置视点  */
    glScalef(3, 0.5, 0.5);      /* 设置模型变换矩阵 */
    glutWireCube(1.0);        /* 绘制线框立方体 */
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); /* 设置视口信息 */
    glMatrixMode(GL_PROJECTION); /* 选择投影矩阵 */
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); /* 设置透视投影变换矩阵 */
    glMatrixMode(GL_MODELVIEW); /* 选择模型视点矩阵 */
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
