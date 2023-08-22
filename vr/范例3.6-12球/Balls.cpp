//#include <GL/glut.h>
//#include <chrono>
//#include <vector>
//
//
//using GLcolor = unsigned int;
//constexpr GLcolor RGB(unsigned char r, unsigned char g, unsigned char b) { return ((GLcolor)(b | (g << 8)) | (r << 16)); }
//constexpr GLcolor GRAY(unsigned char c) { return RGB(c, c, c); }
//constexpr unsigned char GetRValue(GLcolor rgb) { return rgb >> 16; }
//constexpr unsigned char GetGValue(GLcolor rgb) { return rgb >> 8; }
//constexpr unsigned char GetBValue(GLcolor rgb) { return rgb; }
//void glColor3b(GLcolor rgb) { return glColor3f(GetRValue(rgb) / 255., GetGValue(rgb) / 255., GetBValue(rgb) / 255.);}
//
//struct Ball
//{
//    enum : GLint
//    {
//        DEFAULT_SLICES = 64
//        , DEFAULT_STACKS = 64
//    };
//    GLfloat x;
//    GLfloat y;
//    GLfloat z;
//
//    GLdouble radius;
//    GLint slices;
//    GLint stacks;
//    GLcolor color;
//    GLfloat shininess;
//};
//
//
//GLfloat rateRotation = 0.0;
//GLfloat rotationAngle = 0.0;
//GLfloat xAngle = 0.0;
//GLfloat yAngle = 0.0;
//GLfloat zAngle = 0.0;
//GLfloat oldMouseX;
//GLfloat oldMouseY;
//GLint screenWidth = 800;
//GLint screenHeight = 800;
//std::vector<Ball> theseBalls;
//
//
//GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//GLfloat low_shininess[] = { 100.0 };
//
//
//
//
//void display(void)
//{
//    glLoadIdentity();
//    gluLookAt(0, 0, 10, 0, 0, 1, 0.0, 1.0, 0);
//    glPushMatrix();
//    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
//    glRotatef(xAngle, 1.0, 0.0, 0.0);
//    glRotatef(yAngle, 0.0, 1.0, 0.0);
//    glRotatef(zAngle, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColorMaterial(GL_FRONT, GL_SPECULAR);
//    glColor3f(0.2, 0.3, 0.5);
//
//    for(auto& ball : theseBalls)
//    {
//        glPushMatrix();
//
//        glMaterialfv(GL_FRONT, GL_SHININESS, &ball.shininess);
//
//
//        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//        glColor3b(ball.color);
//        glTranslatef(ball.x, ball.y, ball.z);
//        glutSolidSphere(ball.radius, ball.slices, ball.stacks);
//        glPopMatrix();
//    }
//    glPopMatrix();
//    glFlush();
//}
//
//void reshape(int w, int h)
//{
//    GLfloat lightPos[] = { 0.0,0.0,75.0,1.0 };
//
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    glTranslatef(0.0, 0.0, -10.0);
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//}
//
//void onMouseMsg(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON)
//    {
//        if (state == GLUT_DOWN)
//        {
//            rateRotation = 0;
//            rotationAngle = 0;
//            oldMouseX = x;
//            oldMouseY = y;
//        }
//    }
//    if (button == GLUT_RIGHT_BUTTON)
//    {
//        if (state == GLUT_DOWN)
//        {
//            rateRotation += 1.0f;
//        }
//    }
//}
//
//
//void onMotion(int x, int y)
//{
//    GLint deltax = oldMouseX - x;
//    GLint deltay = oldMouseY - y;
//    xAngle += 360 * static_cast<GLfloat>(deltax) / screenWidth;
//    yAngle += 360 * static_cast<GLfloat>(deltay) / screenHeight;
//    zAngle += 360 * static_cast<GLfloat>(deltay) / screenHeight;
//    oldMouseX = x;
//    oldMouseY = y;
//    glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv)
//{
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = { 50.0 };
//    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
//
//    srand(time(0));
//
//	theseBalls =
//	{
//          {-3.75, 3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0X1974AB, 80}
//        , {-1.25, 3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0X1974AB, 5}
//        , {1.25, 3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0X1974AB, 70}
//        , {3.75, 3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0X1974AB, 70}
//        , {-3.75, 0.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XB1B1B1, 80}
//        , {-1.25, 0.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XB1B1B1, 5}
//        , {1.25, 0.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XB1B1B1, 70}
//        , {3.75, 0.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XB1B1B1, 70}
//        , {-3.75, -3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XC5C57B, 80}
//        , {-1.25, -3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XC5C57B, 5}
//        , {1.25,  -3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XC5C57B, 70}
//        , {3.75,  -3.0, 0.0, 1.0, Ball::DEFAULT_SLICES, Ball::DEFAULT_STACKS, 0XC5C57B, 70}
//	};
//
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(screenWidth, screenHeight);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow(argv[0]);
//
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glShadeModel(GL_SMOOTH);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    glHint(GL_LINE_SMOOTH, GL_NICEST);
//
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_COLOR_MATERIAL);
//
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutMouseFunc(onMouseMsg);
//    glutMotionFunc(onMotion);
//    glutMainLoop();
//    return 0;
//}
//


#include <GL/glut.h>
#include <cstdlib>
GLfloat lightPos[] = { 0.0,0.0,75.0,1.0 };
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_diffuse1[] = { 0.7,0.7,0.7,1.0 };
GLfloat mat_diffuse2[] = { 0.8 ,0.8,0.5,1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };


void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };



    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_SMOOTH);



    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);



    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

}



void display(void)

{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glPushMatrix();

    glTranslatef(-3.75, 3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(-1.25, 3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(1.25, 3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(3.75, 3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(-1.25, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(-3.75, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(3.75, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(1.25, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(-1.25, -3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(1.25, -3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(-3.75, -3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(3.75, -3.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glutSolidSphere(1.0, 16, 16);

    glPopMatrix();



    glFlush();

}



void reshape(int w, int h)

{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();



    glTranslatef(0.0, 0.0, -10.0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

}



void keyboard(unsigned char key, int x, int y)

{

    switch (key) {

    case 27:

        exit(0);

        break;

    }

}



int main(int argc, char** argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(500, 500);

    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;

}