#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

class SnakeGame {
public:
    void run();
    void update();

private:
    int N = 50;
    int M = 50;
    int size = 14;
    int w = size * N;
    int h = size * M;
    float timer = 0, delay = 0.1;
    int dir, snakeSize = 2, score = 0, highestScore = 0;
};

struct Snake {
    int x, y;
};

struct Fruit {
    int x, y;
};

extern Snake s[100];
extern Fruit f;

#endif