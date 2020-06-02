#pragma comment(lib, "legacy_stdio_definitions.lib ")
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <cstdlib>

constexpr int checkImageWidth = 64;
constexpr int checkImageHeight = 64;
constexpr int flyImageWidth = 128;
constexpr int flyImageHeight = 128;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte otherImage[checkImageHeight][checkImageWidth][4];
static GLubyte flyImage[flyImageHeight][flyImageWidth][4];

static GLuint texName[4];

#define USE_FLY_TEXTURE false
#define USE_PIC_TEXTURE true

/// <summary>
/// 32X32 bits
/// </summary>
GLubyte fly[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
   0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
   0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
   0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
   0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
   0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
   0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
   0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
   0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
   0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
   0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
   0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
   0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
   0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
   0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08 };

/// <summary>
/// 生成苍蝇纹理
/// </summary>
void makeFlyImages(void)
{
    for (int i = 0; i < flyImageWidth; i++) {
        for (int j = 0; j < flyImageHeight; j++) {
            auto offset = i % 32 * 32 + j % 32;
            *(GLuint*)&flyImage[i][j] = fly[offset / 8] & (1 << (7-(offset % 8))) ? 0XFFFFFFFF : 0XFF000000;
        }
    }
}

void makeCheckImages(void)
{
    for (int i = 0; i < checkImageHeight; i++) {
        for (int j = 0; j < checkImageWidth; j++) {
            int c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            checkImage[i][j][0] = (GLubyte)c;
            checkImage[i][j][1] = (GLubyte)c;
            checkImage[i][j][2] = (GLubyte)c;
            checkImage[i][j][3] = (GLubyte)255;
            c = ((((i & 0x10) == 0) ^ ((j & 0x10)) == 0)) * 255;
            otherImage[i][j][0] = (GLubyte)c;
            otherImage[i][j][1] = (GLubyte)0;
            otherImage[i][j][2] = (GLubyte)0;
            otherImage[i][j][3] = (GLubyte)255;
        }
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    makeFlyImages();
    makeCheckImages();
   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 设置1字节对齐

    glGenTextures(3, texName);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);// 将纹理坐标限制在0.0,1.0的范围之内.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 纹理放大过滤 临近插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 纹理缩小过滤 临近插值

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
        checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        checkImage);

    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
        checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        otherImage);

    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, flyImageWidth,
        flyImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        flyImage);

    auto texture = auxDIBImageLoad(TEXT("meme2.bmp"));
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->sizeX,
        texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
        texture->data);


    glEnable(GL_TEXTURE_2D);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texName[USE_FLY_TEXTURE ? 2 : 0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[USE_FLY_TEXTURE ? 2 : USE_PIC_TEXTURE ? 3 : 1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.41421, 1.0, -1.41421);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.41421, -1.0, -1.41421);
    glEnd();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    default:
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
