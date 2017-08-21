#include "Tile.h"
#include <cmath>

namespace MidasMiner
{
	Tile::Tile()
	{

	}

	Tile::Tile(int x, int y, TileColor color)
	{
		Tile();
		mX = x;
		mY = y;
		mColor = color;
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
		return mColor == t->mColor;
	}

	bool Tile::operator==(const Tile & t)
	{
		return mColor == t.mColor && mX == t.mX && mY == t.mY;
	}

	bool Tile::operator!=(const Tile & t)
	{
		return mColor != t.mColor || mX != t.mX || mY != t.mY;
	}

	Tile::TileColor Tile::GetColor()
	{
		return mColor;
	}

	int Tile::GetX()
	{
		return mX;
	}

	int Tile::GetY()
	{
		return mY;
	}

	void Tile::SetPosition(int x, int y)
	{
		mX = x;
		mY = y;
	}


	Tile::~Tile()
	{
	}
}