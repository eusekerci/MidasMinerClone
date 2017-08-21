#include "GridView.h"

namespace MidasMiner
{
	GridView::GridView(King::Engine& engine, Grid & grid)
	{
		mEngine = &engine;
		mGrid = &grid;

		mGridSizeX = 352.0f;
		mGridSizeY = 352.0f;
		mTileSizeX = 35.0f;
		mTileSizeY = 35.0f;

		mGridTopLeftX = 325.0f;
		mGridTopLeftY = 100.0f;
		mGridBotRightX = 677.0f;
		mGridBotRightY = 452.0f;
		mTileOffsetX = 9.0f;
		mTileOffsetY = 9.0f;
	}

	GridView::~GridView()
	{
	}

	void GridView::Update()
	{
		RenderBackground();
		RenderGrid();
	}

	void GridView::RenderBackground()
	{
		mEngine->Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);
	}

	void GridView::RenderGrid()
	{
		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mEngine->Render(static_cast<King::Engine::Texture>(static_cast<int>(mGrid->GetTile(i, j)->GetColor())), mGridTopLeftX + j * (mTileSizeX + mTileOffsetX), mGridTopLeftY + i * (mTileSizeY + mTileOffsetY));
			}
		}
	}
}