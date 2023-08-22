#include <GL/glut.h>
#include <cstdlib>
#include <map>
#include <string>
#include <ctime>
#include <functional>
#include <mutex>

/// 操作
// 鼠标拖动 修改视角
// P 暂停
// L 改变轨道绘制类型
// D 缩小太阳轨道半径
// U 增大太阳轨道半径
// S 显示/隐藏太阳轨道
// O 显示/隐藏所有轨道
// C 显示正方体而非星球
// R 轨道跟随星球旋转

/// 行星可以多级创建，由名称建立索引
// 行星高度（Y轴）轨道偏移会使得太阳系更加真实一些，每个星球的轨道平面不是完全重合
// 后续可考虑增加轨道中心偏移、倾斜，甚至使用椭圆轨道
// 八大行星根据其实际大致颜色确定

namespace thatboy
{
#ifndef RGB
	using DWORD = unsigned int;
	using COLORREF = DWORD;
	using WORD = unsigned short;
	using BYTE = unsigned char;
	constexpr COLORREF RGB(BYTE r, BYTE g, BYTE b) { return ((COLORREF)(b | (g << 8)) | (r << 16)); }
	constexpr COLORREF GRAY(BYTE c) { return RGB(c, c, c); }
	constexpr BYTE GetRValue(COLORREF rgb) { return rgb >> 16; }
	constexpr BYTE GetGValue(COLORREF rgb) { return rgb >> 8; }
	constexpr BYTE GetBValue(COLORREF rgb) { return rgb; }
#define RGB2glColor3f(rgb) GetRValue(rgb)/255., GetGValue(rgb)/255., GetBValue(rgb)/255.
#endif // ! RGB

	struct Planet
		: public std::map<std::string, Planet>
	{
		using GLcolor = unsigned int;

		enum :int { IDT_FLUSHWINDOW };

		GLfloat planetRadius = 3;		// 星球半径
		GLint planeSlices = 20;			// 经纬线
		GLint planeStacks = 16;			// 经纬线

		GLfloat oribitRadius = 0;		// 轨道半径
		GLfloat oribitSpeed = 2;		// 运行速度
		GLfloat faceSpeed = 2;			// 自传速度
		GLcolor planetcolor = 0XFFFFFF;	// 颜色
		GLfloat oribitAngle = 0;		// 公转角度
		GLfloat faceAngle = 0;			// 自转角度
		GLfloat oribitOffsetY = 0;		// Y方向轨道偏移

		bool showOrbit = true;			// 是否绘制轨道

		Planet(GLfloat planetRadius, GLint planeSlices, GLint planeStacks
			, GLfloat oribitRadius, GLfloat oribitSpeed
			, GLfloat faceSpeed, GLcolor planetcolor
			, GLfloat oribitAngle, GLfloat faceAngle
			, GLfloat oribitOffsetY = 0, bool showOrbit = true)
			: planetRadius(planetRadius)
			, planeSlices(planeSlices)
			, oribitRadius(oribitRadius)
			, oribitSpeed(oribitSpeed)
			, faceSpeed(faceSpeed)
			, planetcolor(planetcolor)
			, oribitAngle(oribitAngle)
			, faceAngle(faceAngle)
			, oribitOffsetY(oribitOffsetY)
			, showOrbit(showOrbit)
		{}
	
		Planet() = default;
		Planet(const Planet&) = default;
		Planet(Planet&&) = default;
		~Planet() = default;
		Planet& operator=(const Planet&) = default;
		Planet& operator=(Planet&&) = default;

		void moveNext()
		{
			if (oribitSpeed != 0)
			{
				if (oribitRadius > 0)
				{
					oribitAngle += oribitSpeed / oribitRadius;

					while (oribitAngle >= 360)
						oribitAngle -= 360;
					while (oribitAngle < 0)
						oribitAngle += 360;
				}
			}
			if (faceSpeed != 0)
			{
				if (planetRadius > 0)
				{
					faceAngle += faceSpeed / planetRadius;

					while (faceAngle >= 360)
						faceAngle -= 360;
					while (faceAngle < 0)
						faceAngle += 360;
				}
			}

			for (auto& p : *this)
				p.second.moveNext();
		}
	};

	namespace SolarSystem
	{
		Planet Sun;

		namespace PlanetControl
		{
			// 控制
			bool ifShowCube = false;
			bool ifShowOrbit = true;
			bool ifOrbitLine = true;
			bool ifAutoRun = true;
			bool ifOribitRotate = true;

			GLfloat rateRotation = 0.0;
			GLfloat rotationAngle = 0.0;
			GLfloat xAngle = 0.0;
			GLfloat yAngle = 0.0;
			GLfloat zAngle = 0.0;
			GLint screenWidth = 1920;
			GLint screenHeight = 1080;
			GLfloat oldMouseX;
			GLfloat oldMouseY;

			void onWindowDsiplay(void);
			void onWindowReshape(int w, int h);
			void onKeyboard(unsigned char key, int x, int y);
			void onTimerFlushWindow(int);
			void onMouseMsg(int button, int state, int x, int y);
			void onMotion(int x, int y);
		}
	}

}

int main(int argc, char** argv)
{
	srand(time(0));

	using thatboy::Planet;
	using thatboy::SolarSystem::Sun;

	// 添加行星
	Sun				= Planet(3, 30, 16, 8.f, -2, -1, 0XDD001B, 0, 0, 0, false);// 绕着屏幕中心转动
	Sun["太阳核心"] = Planet(2.7, 200, 200, 0, -2, 5, 0XEEDB33, 0, 0, false); 
	Sun["水星"]		= Planet(0.6f, 10, 5, 06.0f, 10, rand() % 10 - 5, 0X7C7C7C, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["金星"]		= Planet(0.9f, 16, 10, 10.0f, 13, rand() % 40 - 20, 0XF4CC87, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["地球"]		= Planet(1.2f, 16, 10, 15.0f, 10, 10, 0X007ACC, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["火星"]		= Planet(1.0f, 16, 10, 19.0f, 15, rand() % 40 - 20, 0XC5A26A, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["木星"]		= Planet(1.5f, 16, 10, 25.0f, 22, rand() % 40 - 20, 0XD3D7C0, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["土星"]		= Planet(1.3f, 16, 10, 28.0f, 23, rand() % 40 - 20, 0XDFA14A, rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f);
	Sun["天王星"]	= Planet(2.0f, 16, 10, 32.0f, 30, rand() % 40 - 20, 0XA9CAFD, rand() % 360, rand() % 360, rand() % 400 / 100.f - 2.f);
	Sun["海王星"]	= Planet(3.0f, 16, 10, 40.0f, 15, rand() % 40 - 20, 0X4F82D5, rand() % 360, rand() % 360, rand() % 400 / 100.f - 2.f);

	// 回归速度很慢，设定一个慢速大轨道
	// 冥王星用来演示多级卫星
	Sun["曾经的冥王星"] = Planet(3.f, 16, 10, 70.f, -5, 10, 0XA88285, 180, 180, rand() % 2000 / 100.f - 10.f);

	// 添加二级行星（卫星）、三级卫星、四级卫星
	Sun["金星"]["疑似存在的卫星"] = Planet(0.4, 16, 10, 2.0f, -10, rand() % 40 - 20, 0XF2BBA8, rand() % 360, rand() % 360);
	Sun["地球"]["月球"] = Planet(0.8, 16, 10, 3.0f, -5, rand() % 40 - 20, 0XDFDFDF, rand() % 360, rand() % 360);
	Sun["火星"]["火卫一"] = Planet(0.4f, 16, 10, 3.6f, 12, rand() % 40 - 20, 0X77AA55, rand() % 360, rand() % 360);
	Sun["火星"]["火卫二"] = Planet(0.5f, 16, 10, 2.2f, -7, rand() % 40 - 20, 0XAA22CC, rand() % 360, rand() % 360);
	Sun["木星"]["79颗卫星"] = Planet(0.7f, 16, 10, 3.2f, 5, rand() % 40 - 20, 0XCC8000, rand() % 360, rand() % 360);
	// 添加小行星带，不显示轨道
	for (size_t i = 0; i < 400; i++)
		Sun[std::string("小行星带") + std::to_string(i)]
		= Planet(rand() % 10 / 30., 16, 10, rand() % 80 / 50. + 21.f, rand() % 20 / 3. + 6, rand() % 40/5. - 4
			, thatboy::GRAY(rand() % 40 + 150), rand() % 360, rand() % 360, rand() % 200 / 100.f - 1.f, false);
	Sun["天王星"]["天卫一"] = Planet(0.9f, 16, 10, 6.f, -4.6, rand() % 40 - 20, 0XCC80AA, rand() % 360, rand() % 360);
	Sun["天王星"]["天卫二"] = Planet(1.1f, 16, 10, 6.f, 2.2, rand() % 40 - 20, 0X88CAEE, rand() % 360, rand() % 360);
	Sun["天王星"]["天卫一"]["天卫一.1"] = Planet(0.5f, 16, 10, 2.f, 2, rand() % 40 - 20, 0XBBF0AA, rand() % 360, rand() % 360);
	Sun["天王星"]["天卫二"]["天卫二.1"] = Planet(0.6f, 16, 10, 3.f, -1.5, rand() % 40 - 20, 0XC485F8, rand() % 360, rand() % 360);
	Sun["天王星"]["天卫二"]["天卫二.1"]["天卫二.1.1"] = Planet(0.3f, 16, 10, 1.1f, -3.6, rand() % 40 - 20, 0XF86A5B, rand() % 360, rand() % 360);
	Sun["海王星"]["海卫一"] = Planet(1.f, 16, 10, 6.f, 4, rand() % 40 - 20, 0XC5A26A, rand() % 360, rand() % 360);
	Sun["海王星"]["海卫一"]["海卫一.1"] = Planet(0.5f, 16, 10, 2.f, 3, rand() % 40 - 20, 0X7C7C7C, rand() % 360, rand() % 360);

	// 设定多级卫星
	Sun["曾经的冥王星"]["冥卫一"] = Planet(2.f, 16, 10, 10.f, -10, rand() % 40 - 20, 0X45828A, rand() % 360, rand() % 360);
	Sun["曾经的冥王星"]["冥卫一"]["二级卫星"] = Planet(1.f, 16, 10, 5.f, -9, rand() % 40 - 20, 0X85A23A, rand() % 360, rand() % 360);
	Sun["曾经的冥王星"]["冥卫一"]["二级卫星"]["三级卫星"] = Planet(0.5f, 16, 10, 2.f, 9, rand() % 40 - 20, 0XF2BBA8, rand() % 360, rand() % 360);
	Sun["曾经的冥王星"]["冥卫一"]["二级卫星"]["三级卫星"]["四级卫星"] = Planet(0.4f, 16, 10, 1.f, 5, rand() % 40 - 20, 0XCC80AA, rand() % 360, rand() % 360);

	// 初始化OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(R"(NO MAN'S SKY)");
	glutFullScreen();
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

	glutDisplayFunc(thatboy::SolarSystem::PlanetControl::onWindowDsiplay);
	glutReshapeFunc(thatboy::SolarSystem::PlanetControl::onWindowReshape);
	glutKeyboardFunc(thatboy::SolarSystem::PlanetControl::onKeyboard);
	glutTimerFunc(20, thatboy::SolarSystem::PlanetControl::onTimerFlushWindow, Planet::IDT_FLUSHWINDOW);
	glutMouseFunc(thatboy::SolarSystem::PlanetControl::onMouseMsg);
	glutMotionFunc(thatboy::SolarSystem::PlanetControl::onMotion);

	// 交予控制权
	glutMainLoop();
	return 0;
}

void thatboy::SolarSystem::PlanetControl::onWindowDsiplay(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  //加载单位矩阵  
	gluLookAt(38, 50, 38, 0.0, -20.0, 0.0, 0.0, 1.0, 0);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);

	auto drawCircle = [](int x, int y, int r, float startAngle = 0)
	{
		constexpr GLfloat PI = 3.141592654;
		int n = (static_cast<int>(sqrt(r) * 18) | 1) + 1;	// 确保偶数个点
		glRotatef(startAngle, 0, 1, 0);
		glBegin(ifOrbitLine ? GL_LINES : GL_POLYGON);
		for (int i = 0; i < n; i++)
		{
			GLfloat curAnlge = 2 * PI / n * i;
			glVertex3f(x + r * cos(curAnlge), 0, y + r * sin(curAnlge));
		}
		glEnd();
		glRotatef(startAngle, 0, -1, 0);
	};

	std::function<void(const Planet&)> drawPlanet;
	drawPlanet = [&drawPlanet, &drawCircle](const Planet& planet)
	{
		// 绘制轨道(基于父星坐标系）
		if (ifShowOrbit && planet.showOrbit)
		{
			glTranslatef(0, planet.oribitOffsetY, 0);
			glColor3f(RGB2glColor3f(planet.planetcolor));
			drawCircle(0, 0, planet.oribitRadius, ifOribitRotate ? planet.oribitAngle : 0);
			glTranslatef(0, -planet.oribitOffsetY, 0);
		}
		// 公转
		glRotatef(planet.oribitAngle, 0, 1, 0);
		glTranslatef(planet.oribitRadius, 0, 0);
		glRotatef(planet.oribitAngle, 0, -1, 0);		// 恢复角度

		glTranslatef(0, planet.oribitOffsetY, 0);
		for (auto& pMap : planet)
			drawPlanet(pMap.second);
		glTranslatef(0, -planet.oribitOffsetY, 0);

		glRotatef(planet.oribitAngle, 0, 1, 0);		// 
		// 自转
		glRotatef(planet.faceAngle, 0, 1, 0);

		// 轨道偏移
		glTranslatef(0, planet.oribitOffsetY, 0);

		glColor3f(RGB2glColor3f(planet.planetcolor));
		if (ifShowCube)
			glutWireCube(planet.planetRadius);
		else
			glutWireSphere(planet.planetRadius, planet.planeSlices, planet.planeStacks);
		// 轨道偏移恢复
		glTranslatef(0, -planet.oribitOffsetY, 0);
		// 自转恢复
		glRotatef(planet.faceAngle, 0, -1, 0);

		// 公转恢复
		glTranslatef(-planet.oribitRadius, 0, 0);
		glRotatef(planet.oribitAngle, 0, -1, 0);	// 恢复父环境
	};

	// 递归绘制
	glPushMatrix();
	drawPlanet(Sun);
	glPopMatrix();

	glutSwapBuffers();
}

void thatboy::SolarSystem::PlanetControl::onWindowReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 5.0, 180);
	glMatrixMode(GL_MODELVIEW);
}

void thatboy::SolarSystem::PlanetControl::onKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		ifAutoRun = !ifAutoRun;
		break;
	case 'l':
	case 'L':
		ifOrbitLine = !ifOrbitLine;
		break;
	case 'd':
	case 'D':
		if (Sun.oribitRadius > 0)
			Sun.oribitRadius -= 0.1;
		else
			Sun.oribitRadius = 0;
		break;
	case 'u':
	case 'U':
		Sun.oribitRadius += 0.1;
		break;
	case 's':
	case 'S':
		Sun.showOrbit = !Sun.showOrbit;
		break;
	case 'o':
	case 'O':
		ifShowOrbit = !ifShowOrbit;
		break;
	case 'c':
	case 'C':
		ifShowCube = !ifShowCube;
		break;
	case 'r':
	case 'R':
		ifOribitRotate = !ifOribitRotate;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void thatboy::SolarSystem::PlanetControl::onTimerFlushWindow(int id)
{
	if (id != Planet::IDT_FLUSHWINDOW)
		return;
	if (ifAutoRun)
		Sun.moveNext();
	glutPostRedisplay();
	return glutTimerFunc(20, onTimerFlushWindow, Planet::IDT_FLUSHWINDOW);
}

void thatboy::SolarSystem::PlanetControl::onMouseMsg(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			rateRotation = 0;
			rotationAngle = 0;
			oldMouseX = x;
			oldMouseY = y;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			rateRotation += 1.0f;
		}
	}
}

void thatboy::SolarSystem::PlanetControl::onMotion(int x, int y)
{
	GLint deltax = oldMouseX - x;
	GLint deltay = oldMouseY - y;
	xAngle += 360 * static_cast<GLfloat>(deltax) / screenWidth;
	yAngle += 360 * static_cast<GLfloat>(deltay) / screenHeight;
	zAngle += 360 * static_cast<GLfloat>(deltay) / screenHeight;
	oldMouseX = x;
	oldMouseY = y;
	glutPostRedisplay();
}
