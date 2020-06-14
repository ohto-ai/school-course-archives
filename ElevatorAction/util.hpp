#pragma once
#include <utility>
int randint(int min_val, int max_val);
float randfloat(float min_val, float max_val);
float to_x1(int x, int y, float width, float height);
float to_y1(int x, int y, float width, float height);
float to_x2(int x, int y, float width, float height);
float to_y2(int x, int y, float width, float height);
void v2normalize(float *x, float *y);
void v2normalize(std::pair<float, float> *xy);
float v2len(float x, float y);
float v2len(std::pair<float, float> xy);
float fsgn(float x);
float fsgn2(float x);
int fcmp(float x, float y, float epsillon = 0.005f);
bool feq(float x, float y, float epsillon = 0.005f);
bool fle(float x, float y, float epsillon = 0.005f);
bool fge(float x, float y, float epsillon = 0.005f);
bool flt(float x, float y, float epsillon = 0.005f);
bool fgt(float x, float y, float epsillon = 0.005f);
float x2fx(int x);
float y2fy(int y);
int fx2x(float fx);
int fy2y(float fy);
void drawString(void * font, float x, float y, char *string);
void drawStringCentered(void *font, float y, char *string);
void beginText();
void endText();
