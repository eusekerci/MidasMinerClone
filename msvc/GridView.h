#ifndef GRIDVIEW_H_
#define GRIDVIEW_H_

#pragma once

#include <king\Engine.h>
#include "Grid.h"
#include "Controller.h"
#include <vector>
#include <map>
#include <algorithm>

namespace MidasMiner
{
	class Controller;

	class GridView
	{
	public:
		struct Pixel
		{
			float x;
			float y;
		};

		struct Position
		{
			int x;
			int y;
		};

		struct TileTween
		{
			Tile* tile;
			Tile::TileColor color;
			float currentPixelX;
			float currentPixelY;
			float toPixelX;
			float toPixelY;
			float time;
			float priority;

			bool operator<(const TileTween& rhs) const
			{
				return priority < rhs.priority;
			}

			bool compare(int i, int j) { return i < j; }
		};

		GridView() {};
		GridView(King::Engine& engine, Grid& grid);
		~GridView();

		void Update();
		void RenderBackground();
		void RenderGrid();

		bool IsTileClicked(Pixel pi);
		bool IsTileClicked(float x, float y);
		Tile* GetTileClicked(Pixel pi);
		Tile* GetTileClicked(float x, float y);

		void OnFirstSelected(Tile& t);
		void OnResetSelection();

		void TileMoveTween(Tile& t, int oldX, int oldY);
		void SpawnTileTween(Tile& t, int order);
		void SwapTileTween(Tile& t1, Tile& t2, int order);

		Pixel PositionToPixel(Position pos);
		Position PixelToPosition(Pixel pi);

		bool WaitForAnim();

	private:
		King::Engine* mEngine;
		Controller* mController;
		Grid* mGrid;
		std::vector<TileTween> mDropingTiles;
		
		float mGridSizeX;
		float mGridSizeY;
		float mTileSizeX;
		float mTileSizeY;
		
		float mGridTopLeftX;
		float mGridTopLeftY;
		float mGridBotRightX;
		float mGridBotRightY;
		float mTileOffsetX;
		float mTileOffsetY;

		bool mIsTileSelected;
		float mSelectedTileX;
		float mSelectedTileY;

		float mTileTweenSpeed;
	};
}

#endif // GRIDVIEW_H_