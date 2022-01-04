#include "PositionScoreCompare.h"

using namespace std;
using namespace ai;

bool PositionScoreCompare::operator> (Position& a, Position& b)
{
    return a.getScore()>b.getScore();
}