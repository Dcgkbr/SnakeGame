#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>


bool gameOver;
const int width = 20;
const int height = 10;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int x, y, foodx, foody, score;
vector<int> tailX;
vector<int> tailY;
int tailLength;
void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodx = rand() % width;
    foody = rand() % height;
    score = 0;
    tailLength = 0;
}
