#include "Grid.h"

namespace MidasMiner
{
	Grid::Grid()
		: mWidth(8)
		, mHeight(8)
		, mIsInitiliazed(false)
	{
		srand((unsigned int)time(0));

		PrintGrid();
	}

	Grid::~Grid()
	{
	}

	Tile* Grid::GetTile(int x, int y)
	{
		return mGrid[y]->at(x);
	}

	void Grid::SetGrid(std::vector<std::vector<Tile*>*>& grid)
	{
		for (int i = 0; i < mHeight; i++)
		{
			std::vector< Tile* > * newVec = new std::vector< Tile* >();
			for (int j = 0; j < mWidth; j++)
			{
				newVec->push_back(grid[i]->at(j));
				newVec->back()->SetPosition(j, i);
			}
			mGrid.push_back(newVec);
		}

		mIsInitiliazed = true;

		PrintGrid();
	}

	Tile * Grid::RandomTile()
	{
		int r = rand() % 5;
		return TilePools[r]->Get();
	}

	void Grid::RemoveTile(int x, int y)
	{
		TilePools[static_cast<int>(GetTile(x, y)->GetColor())-1]->Kill(GetTile(x, y));
		mGrid[y]->erase(mGrid[y]->begin()+x);
		mGrid[y]->insert(mGrid[y]->begin()+x, new Tile());
	}

	void Grid::ReOrganizeColumn(int x)
	{
		int count = 0;
		std::vector<int> index;
		
		for (int i=0; i<mHeight; i++)
		{
			GetTile(x, i)->SetPosition(x, i);

			if (GetTile(x, i)->IsEmpty())
			{
				count++;
				index.push_back(i);
			}
		}

		if (index.size() > 0)
		{
			int howManyWillDrop = index[0];

			for (int i = howManyWillDrop; i > 0; i--)
			{
				Swap(*GetTile(x, i-1), *GetTile(x, i - 1 + count));
			}
		}
	}

	void Grid::FillEmptyTiles()
	{
		for (int i=0; i<mWidth; i++)
		{
			for (int j=0; j<mHeight; j++)
			{
				if (GetTile(j,i)->IsEmpty())
				{
					AddTile(j, i);
				}
			}
		}
	}

	void Grid::AddTile(int x, int y)
	{
		TilePools[static_cast<int>(GetTile(x, y)->GetColor())]->Kill(GetTile(x, y));
		mGrid[y]->erase(mGrid[y]->begin()+(x));
		mGrid[y]->insert(mGrid[y]->begin()+x, RandomTile());
		GetTile(x, y)->SetPosition(x, y);
	}

	void Grid::AddTile(int x, int y, Tile * t)
	{
		TilePools[static_cast<int>(GetTile(x, y)->GetColor())]->Kill(GetTile(x, y));
		mGrid[y]->erase(mGrid[y]->begin()+x);
		mGrid[y]->insert(mGrid[y]->begin()+x, t);
		t->SetPosition(x, y);
	}

	void Grid::Swap(Tile& t1, Tile& t2)
	{
		int t1X = t1.GetX();
		int t1Y = t1.GetY();
		int tempX = t2.GetX();
		int tempY = t2.GetY();
		std::swap(t1, t2);
		mGrid[t1Y]->at(t1X)->SetPosition(t1X, t1Y);
		mGrid[tempY]->at(tempX)->SetPosition(tempX, tempY);
	}

	std::vector<Tile*> Grid::GetRow(int x)
	{
		return *mGrid[x];
	}

	std::vector<Tile*> Grid::GetColumn(int y)
	{
		std::vector<Tile*> res;
		for (auto a : mGrid)
		{
			res.push_back(a->at(y));
		}
		
		return res;
	}

	std::vector<Tile*> Grid::GetByColor(Tile::TileColor color)
	{
		std::vector<Tile*> res;
		for (auto a : mGrid)
		{
			for (auto b : *a)
			{
				if (b->GetColor() == color)
				{
					res.push_back(b);
				}
			}
		}

		return res;
	}

	bool Grid::IsTileEmpty(int x, int y)
	{
		return GetTile(x, y)->IsEmpty();
	}

	void Grid::PrintGrid()
	{
		for (auto a : mGrid)
		{
			for (auto b : *a)
			{
				std::cout << b->GetColor() << "(" << b->GetX() << "," << b->GetY() << ") ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	int Grid::GetWidth()
	{
		return mWidth;
	}

	int Grid::GetHeight()
	{
		return mHeight;
	}

	bool Grid::IsInitiliazed()
	{
		return mIsInitiliazed;
	}
}