#include <GL/glut.h>
#include <cstdlib>
void display(void)
{
    /* �����ɫ����  */
    glClear(GL_COLOR_BUFFER_BIT);
    /* ����һ����ɫ����Σ�ָ���ĸ����������  */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    /* ������ʼ�������ڻ������е�OpenGL�������á�*/
    glFlush();
}

void init(void)
{
    /* �ƶ������ɫ 	*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /* ����ͶӰ�任��ʽ  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*ָ�����ڵĳ�ʼ��С��λ���Լ���ʾģʽ���������RGBAģʽ��
 *��һ������Ϊhello�Ĵ���
 *����init����.
 *ע����ʾ����.
 * ������ѭ���������¼�*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
