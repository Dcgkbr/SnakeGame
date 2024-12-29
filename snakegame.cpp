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
void draw() {
    clear();
    for (int i = 0; i < width + 2; i++)
        printw("#");
    printw("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printw("#");
            if (i == y && j == x)
                printw("O");
            else if (i == foody && j == foodx)
                printw("F");
            else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printw("o");
                        printTail = true;
                    }
                }
                if (!printTail)
                    printw(" ");
            }
            if (j == width - 1)
                printw("#");
        }
        printw("\n");
    }

    for (int i = 0; i < width + 2; i++)
        printw("#");
    
    printw("\nScore: %d\n", score);
}
