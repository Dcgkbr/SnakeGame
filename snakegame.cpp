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
void input() {
    keypad(stdscr, TRUE);
    halfdelay(1); // wait for input for a short period
    int c = getch();
    
    switch (c) {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}
void logic() {
    int prevX = tailX.empty() ? x : tailX[0];
    int prevY = tailY.empty() ? y : tailY[0];
    int prev2X, prev2Y;

    tailX.insert(tailX.begin(), x);
    tailY.insert(tailY.begin(), y);
    
    if (tailLength > 0) {
        prev2X = tailX[1];
        prev2Y = tailY[1];
        for (int i = 1; i < tailLength; i++) {
            tailX[i] = prevX;
            tailY[i] = prevY;

            prevX = tailX[i + 1];
            prevY = tailY[i + 1];
        }
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    if (x == foodx && y == foody) {
        score += 10;
        foodx = rand() % width;
        foody = rand() % height;
        tailLength++;
    }

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
}
