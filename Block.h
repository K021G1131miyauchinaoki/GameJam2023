#pragma once
#include"Vector2.h"
class Block {
	Block(int x_, int y_) :x(x_), y(y_) {};
	int x;
	int y;
	Vector2 pos;
};

class Mino {
private:
static const int MINO_HEIGHT=4;
static const int MINO_WIDTH=4;
public:
    Block blocks[] = [new Block(-1, 0), new Block(0, 0), new Block(0, -1), new Block(1, 0)];
    //switch (this.shape) {
    //case 0: blocks = [new Block(-1, 0), new Block(0, 0), new Block(0, -1), new Block(1, 0)]; break; //T
    //case 1: blocks = [new Block(-1, -1), new Block(0, -1), new Block(0, 0), new Block(1, 0)]; break; //Z
    //case 2: blocks = [new Block(-1, 0), new Block(0, 0), new Block(0, -1), new Block(1, -1)]; break; //S
    //case 3: blocks = [new Block(-1, -2), new Block(-1, -1), new Block(-1, 0), new Block(0, 0)]; break; //L
    //case 4: blocks = [new Block(0, -2), new Block(0, -1), new Block(-1, 0), new Block(0, 0)]; break; //J
    //case 5: blocks = [new Block(-1, -1), new Block(-1, 0), new Block(0, 0), new Block(0, -1)]; break; //O
    //case 6: blocks = [new Block(-2, 0), new Block(-1, 0), new Block(0, 0), new Block(1, 0)]; break; //I
    //}
};