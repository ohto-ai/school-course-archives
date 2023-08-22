#pragma once
class Game;

void myKeyboardFunc( unsigned char key, int x, int y );
void mySpecialKeyFunc( int key, int x, int y );

void drawScene(void);

void initRendering();
void resizeWindow(int w, int h);

void generate_levels(Game *game);
