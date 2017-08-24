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
		mTileTweenSpeed = 15.0f;
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
		if (!mGrid->IsInitiliazed())
			return;

		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (mGrid->GetTile(j, i)->IsReady() && !mGrid->GetTile(j,i)->IsEmpty())
					mEngine->Render(static_cast<King::Engine::Texture>(static_cast<int>(mGrid->GetTile(j, i)->GetColor())), mGridTopLeftX + j * (mTileSizeX + mTileOffsetX), mGridTopLeftY + i * (mTileSizeY + mTileOffsetY));
			}
		}

		//int k = 0;
		int priority;
		if (mDropingTiles.size() > 0)
			priority = mDropingTiles[0].priority;
		for (unsigned int k=0; k<mDropingTiles.size(); k++)		
		{
			if (priority < mDropingTiles[k].priority)
				break;
			mDropingTiles[k].tile->SetReady(false);
			//if(!mDropingTiles[k].tile->IsEmpty())
			if(mDropingTiles[k].color != Tile::COLOR_NULL)
				mEngine->Render(static_cast<King::Engine::Texture>(static_cast<int>(mDropingTiles[k].color)), mDropingTiles[k].currentPixelX, mDropingTiles[k].currentPixelY);
			
			mDropingTiles[k].time -= mEngine->GetLastFrameSeconds();
			float dirX = mDropingTiles[k].toPixelX - mDropingTiles[k].currentPixelX;
			float dirY = mDropingTiles[k].toPixelY - mDropingTiles[k].currentPixelY;
			
			if(abs(dirX) - mTileTweenSpeed > 0)
				mDropingTiles[k].currentPixelX += dirX > 0.01f ? mTileTweenSpeed : mTileTweenSpeed * -1;
			if(abs(dirY) - mTileTweenSpeed > 0)
				mDropingTiles[k].currentPixelY += dirY > 0.01f ? mTileTweenSpeed : mTileTweenSpeed * -1;
			
			if (mDropingTiles[k].time <= 0.01f)
			{
				mDropingTiles[k].tile->SetReady(true);
				mDropingTiles.erase(std::remove_if(mDropingTiles.begin(), mDropingTiles.end(), [&](TileTween const & t) {
					return t.tile == mDropingTiles[k].tile;
				}), mDropingTiles.end());
			}
		}

		/*if (!mAnimationQueue.empty() > 0)
		{
			TileTween tween = mAnimationQueue.top();
			if (!tween.tile->IsEmpty())
				mEngine->Render(static_cast<King::Engine::Texture>(static_cast<int>(tween.tile->GetColor())), tween.currentPixelX, tween.currentPixelY);

			tween.time -= mEngine->GetLastFrameSeconds();
			float dirX = tween.toPixelX - tween.currentPixelX;
			float dirY = tween.toPixelY - tween.currentPixelY;

			if (abs(dirX) - mTileTweenSpeed > 0)
				tween.currentPixelX += dirX > 0.01f ? mTileTweenSpeed : mTileTweenSpeed * -1;
			if (abs(dirY) - mTileTweenSpeed > 0)
				tween.currentPixelY += dirY > 0.01f ? mTileTweenSpeed : mTileTweenSpeed * -1;

			std::cout << tween.time << std::endl;

			if (tween.time <= 0.01f)
			{
				mAnimationQueue.top().tile->SetReady(true);
				mAnimationQueue.pop();
			}
			else
			{
				mAnimationQueue.pop();
				mAnimationQueue.push(tween);
			}
		}*/

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

	void GridView::OnResetSelection()
	{
		mIsTileSelected = false;
	}

	void GridView::TileMoveTween(Tile & t, int oldX, int oldY)
	{
		
	}

	void GridView::SpawnTileTween(Tile & t, int order)
	{
		Pixel pi = PositionToPixel(Position{ t.GetX(), t.GetY() });
		TileTween tween{ &t, t.GetColor(), pi.x, pi.y - mGridSizeY, pi.x, pi.y, mGridSizeY / (mTileTweenSpeed / mEngine->GetLastFrameSeconds()) , order};

		mDropingTiles.push_back(tween);
		std::sort(mDropingTiles.begin(), mDropingTiles.end());
	}

	void GridView::SwapTileTween(Tile & t1, Tile & t2, int order)
	{

		Pixel pi1 = PositionToPixel(Position{ t1.GetX(), t1.GetY() });
		Pixel pi2 = PositionToPixel(Position{ t2.GetX(), t2.GetY() });
		float mTime = (abs(pi1.x - pi2.x) + abs(pi1.y - pi2.y)) / (mTileTweenSpeed / mEngine->GetLastFrameSeconds());
		TileTween tween1{ &t1, t1.GetColor(), pi2.x, pi2.y, pi1.x, pi1.y, mTime , order};
		TileTween tween2{ &t2, t2.GetColor(), pi1.x, pi1.y, pi2.x, pi2.y, mTime , order};

		mDropingTiles.push_back(tween1);
		mDropingTiles.push_back(tween2);
		std::sort(mDropingTiles.begin(), mDropingTiles.end());
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

	bool GridView::WaitForAnim()
	{
		return !mDropingTiles.empty();
	}
}