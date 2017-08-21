#ifndef GRIDVIEW_H_
#define GRIDVIEW_H_

#pragma once

#include <king\Engine.h>
#include "Grid.h"
#include "Controller.h"

namespace MidasMiner
{
	class Controller;

	class GridView
	{
	public:
		GridView() {};
		GridView(King::Engine& engine, Grid & grid);
		~GridView();

		void Update();
		void RenderBackground();
		void RenderGrid();

	private:
		King::Engine* mEngine;
		Controller* mController;
		Grid* mGrid;
		
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
	};
}

#endif // GRIDVIEW_H_