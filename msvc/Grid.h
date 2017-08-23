#pragma once

#include <vector>
#include <ctime>
#include "Tile.h"
#include "PoolContainer.h"
#include <iostream>

namespace MidasMiner
{
	class Grid
	{
	public:
		Grid();
		~Grid();

		Tile* GetTile(int x, int y);
		void SetGrid(std::vector< std::vector < Tile* >* >& grid);
		Tile* RandomTile();
		void RemoveTile(int x, int y);
		void ReOrganizeColumn(int y);
		void FillEmptyTiles();
		void AddTile(int x, int y);
		void AddTile(int x, int y, Tile* t);
		void Swap(Tile& t1, Tile& t2);
		std::vector< Tile*> GetRow(int x);
		std::vector< Tile*> GetColumn(int y);
		std::vector< Tile*> GetByColor(Tile::TileColor color);
		bool IsTileEmpty(int x, int y);
		void PrintGrid();
		int GetWidth();
		int GetHeight();
		bool IsInitiliazed();

	private:
		int mWidth;
		int mHeight;
		bool mIsInitiliazed;
		std::vector< std::vector< Tile * > * > mGrid;
	};
}
