#include "Tile.h"
#include <cmath>

namespace MidasMiner
{
	Tile::Tile()
	{
	}

	Tile::Tile(Tile::TileType t, int x, int y)
	{
		Tile();
		mType = t;
		mX = x;
		mY = y;
	}

	bool Tile::IsAdjacent(Tile* t)
	{
		if (abs(abs(t->mY) - abs(mY)) == 1 && t->mX == mX)
			return true;
		else if (abs(abs(t->mX) - abs(mX)) == 1 && t->mY == mY)
			return true;
		else
			return false;
	}

	bool Tile::IsEqual(Tile* t)
	{
		return mType == t->mType && mX == t->mX && mY == t->mY;
	}

	bool Tile::operator==(const Tile & t)
	{
		return mType == t.mType && mX == t.mX && mY == t.mY;
	}


	Tile::~Tile()
	{
	}
}