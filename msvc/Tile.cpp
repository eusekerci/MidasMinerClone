#include "Tile.h"
#include <cmath>

namespace MidasMiner
{
	Tile::Tile()
	{
		mColor = COLOR_NULL;
		mX = 0;
		mY = 0;
		mIsReady = false;
	}

	Tile::Tile(int x, int y, TileColor color)
	{
		Tile();
		mX = x;
		mY = y;
		mColor = color;
		mIsReady = false;
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

	bool Tile::IsSameColor(Tile* t)
	{
		return mColor == t->mColor;
	}

	bool Tile::IsSameColor(TileColor color)
	{
		return color == mColor;
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

	bool Tile::IsEmpty()
	{
		return mColor == COLOR_NULL;
	}

	bool Tile::IsReady()
	{
		return mIsReady;
	}

	void Tile::SetReady(bool r)
	{
		mIsReady = r;
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