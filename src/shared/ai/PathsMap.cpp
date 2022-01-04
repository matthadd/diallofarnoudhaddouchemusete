#include "PathsMap.h"
#include "math.h"
#include <cmath>

using namespace ai;
using namespace std;

std::vector<std::pair<int,int>> PathsMap::_map = {};

PathsMap::PathsMap (state::UnitInstance* unit, int height, int width)
{
    _unit = unit;
    _height = height;
    _width = width;
    _reachablePositions = {};
}

PathsMap::~PathsMap () {}


std::vector<Position> PathsMap::getReachablePositions ()
{
    Position unitPosition(_unit->getX(), _unit->getY());
    for(auto position : _map)
    {
        Position* pos = new Position(position.first, position.second);
        if(distance(*pos, unitPosition) <= _unit->getMoveRange())
        {
            _reachablePositions.push_back(*pos);
        }
        else
        {
            delete(pos);
        }
    }
    return _reachablePositions;
}

void PathsMap::spreadScore (Position p, int score){};

double PathsMap::distance (Position a, Position b) const
{
    return sqrt( pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(),2) );
}

void PathsMap::init()
{
    for(size_t i = 0; i < _width - 1; i++)
        for(size_t j =0 ; j < _height - 1; j++)
        {
            _map.push_back(std::pair<int,int>(i, j));
        }
}

std::pair<int, int> PathsMap::bestPosition()
{

}