#include "Position.h"

using namespace std;
using namespace ai;

Position::Position(int x, int y, double score=0.0)
{
    _x = x;
    _y=y;
    _score = score;
}

int Position::getX () const
{
    return _x;
}
int  Position::getY () const
{
    return _y;
}
double Position::getScore () const
{
    return _score;
}
void Position::setScore (double newScore) 
{
    _score = newScore;
}

