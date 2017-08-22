#pragma once

#include <vector>
#include <ctime>
#include "Tile.h"
#include "PoolContainer.h"

namespace MidasMiner
{
	class Grid
	{
	public:
		Grid();
		~Grid();

		Tile* GetTile(int x, int y);
		Tile* RandomTile();

	private:
		int mWidth;
		int mHeight;
		std::vector< std::vector< Tile * > * > mGrid;
	};
}
