#ifndef TILE_H_
#define TILE_H_

#pragma once

#include "Renderer.h"

namespace MidasMiner
{
	class Renderer;

	class Tile : public Renderer
	{
	public:
		enum TileColor
		{
			COLOR_NULL,
			COLOR_BLUE,
			COLOR_GREEN,
			COLOR_PURPLE,
			COLOR_RED,
			COLOR_YELLOW
		};

		Tile();
		~Tile();
		Tile(int x, int y, TileColor color);

		bool IsAdjacent(Tile* newTile);
		bool IsSameColor(Tile* tile);
		bool IsSameColor(TileColor color);
		bool operator==(const Tile& t);
		bool operator!=(const Tile& t);

		TileColor GetColor();
		int GetX();
		int GetY();
		float GetExactX();
		float GetExactY();
		void SetTarget(float x, float y);
		bool IsEmpty();
		bool IsReady();
		void SetReady(bool r);
		void SetPosition(int x, int y);
		Renderer::RenderValues GetRenderValues(float anchorX, float anchorY, float tick);

	private:
		float mX;
		float mY;
		float mTargetX;
		float mTargetY;
		bool mIsReady;
		float mMoveSpeed;
		Tile::TileColor mColor;
	};
}

#endif // TILE_H_