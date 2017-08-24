#ifndef GRIDVIEW_H_
#define GRIDVIEW_H_

#pragma once

#include <king\Engine.h>
#include "Grid.h"
#include "Controller.h"
#include "ScoreManager.h"
#include <vector>
#include <map>
#include <algorithm>

namespace MidasMiner
{
	class Controller;
	class ScoreManager;

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

		GridView() {};
		GridView(King::Engine& engine, Grid& grid, ScoreManager& score);
		~GridView();

		void Init();
		void Update();
		void RenderBackground();
		void RenderGrid();
		void RenderUI();

		bool IsTileClicked(Pixel pi);
		bool IsTileClicked(float x, float y);
		Tile* GetTileClicked(Pixel pi);
		Tile* GetTileClicked(float x, float y);

		void OnFirstSelected(Tile& t);
		void OnResetSelection();

		Pixel PositionToPixel(Position pos);
		Position PixelToPosition(Pixel pi);

	private:
		King::Engine* mEngine;
		Controller* mController;
		Grid* mGrid;
		ScoreManager* mScoreManager;
		
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
	};
}

#endif // GRIDVIEW_H_