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

		mIsTileSelected = false;
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

		if (mIsTileSelected)
		{
			mEngine->Render(King::Engine::TEXTURE_SELECTION, mSelectedTileX, mSelectedTileY);
		}
	}

	bool GridView::IsTileClicked(Pixel pi)
	{
		return (pi.x > mGridTopLeftX && pi.x < mGridBotRightX && pi.y > mGridTopLeftY && pi.y < mGridBotRightY);
	}

	bool GridView::IsTileClicked(float x, float y)
	{
		Pixel pi{ x, y };
		return IsTileClicked(pi);
	}


	Tile* GridView::GetTileClicked(Pixel pi)
	{
		Position pos = PixelToPosition(pi);

		return mGrid->GetTile(pos.x, pos.y);
	}

	Tile* GridView::GetTileClicked(float x, float y)
	{
		Pixel pi{ x, y };
		return GetTileClicked(pi);
	}

	void GridView::OnFirstSelected(Tile& t)
	{
		mIsTileSelected = true;

		Position pos{ t.GetX(), t.GetY() };
		Pixel pi = PositionToPixel(pos);

		mSelectedTileX = pi.x;
		mSelectedTileY = pi.y;
	}

	void GridView::OnSecondSelected(Tile& t)
	{

	}

	void GridView::OnResetSelection()
	{
		mIsTileSelected = false;
	}

	GridView::Pixel GridView::PositionToPixel(Position pos)
	{
		float piX = mGridTopLeftX + pos.x * (mTileSizeX + mTileOffsetX);
		float piY = mGridTopLeftY + pos.y * (mTileSizeY + mTileOffsetY);

		return Pixel{ piX, piY };
	}

	GridView::Position GridView::PixelToPosition(Pixel pi)
	{
		int tileX = static_cast<int>(pi.x - mGridTopLeftX) / static_cast<int>(mTileSizeX + mTileOffsetX);
		int tileY = static_cast<int>(pi.y - mGridTopLeftY) / static_cast<int>(mTileSizeY + mTileOffsetY);
		
		return Position{ tileX, tileY };
	}
}