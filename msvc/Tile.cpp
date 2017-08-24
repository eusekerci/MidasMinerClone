#include "Tile.h"
#include <cmath>

namespace MidasMiner
{
	class Renderer;

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
		mX = static_cast<float>(x);
		mY = static_cast<float>(y);
		mColor = color;
		mIsReady = false;
		mRenderValues.Rotation = 0;
		mRenderValues.SizeX = 44.0f;
		mRenderValues.SizeY = 44.0f;
		mRenderValues.Texture = static_cast<King::Engine::Texture>(static_cast<int>(mColor));	
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
		return static_cast<int>(mX);
	}

	int Tile::GetY()
	{
		return static_cast<int>(mY);
	}

	float Tile::GetExactX()
	{
		return mX;
	}

	float Tile::GetExactY()
	{
		return mY;
	}

	void Tile::SetTarget(float x, float y)
	{
		mTargetX = x;
		mTargetY = y;
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
		mX = static_cast<float>(x);
		mY = static_cast<float>(y);
	}

	Renderer::RenderValues Tile::GetRenderValues(float anchorX, float anchorY, float tick)
	{
		if (!IsReady())
		{
			mX += (mTargetX > mX) ? tick * mMoveSpeed : -1 * tick * mMoveSpeed;
			mY += (mTargetY > mY) ? tick * mMoveSpeed : -1 * tick * mMoveSpeed;

			if (abs(mX - mTargetX) < tick*mMoveSpeed && abs(mY - mTargetY) < tick*mMoveSpeed)
			{
				mX = mTargetX;
				mY = mTargetY;
			}
		}
		else
		{
			mX = mTargetX;
			mY = mTargetY;
		}

		mRenderValues.PosX = mX * mRenderValues.SizeX + anchorX;
		mRenderValues.PosY = mY * mRenderValues.SizeY + anchorY;

		return mRenderValues;
	}

	Tile::~Tile()
	{
	}
}