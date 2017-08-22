#include "Grid.h"

namespace MidasMiner
{
	Grid::Grid()
		: mWidth(8)
		, mHeight(8)
	{
		for (int i = 0; i < mHeight; i++)
		{
			std::vector< Tile* > * newVec = new std::vector< Tile* >();
			for (int j = 0; j < mWidth; j++)
			{
				newVec->push_back(RandomTile());
				newVec->back()->SetPosition(i, j);
			}
			mGrid.push_back(newVec);
		}

		srand(time(NULL));
	}

	Grid::~Grid()
	{
	}

	Tile* Grid::GetTile(int x, int y)
	{
		return mGrid[x]->at(y);
	}

	Tile * Grid::RandomTile()
	{
		int r = rand() % 5;
		return TilePools[r]->Get();
	}
}