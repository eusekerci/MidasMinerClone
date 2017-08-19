#pragma once

#include <vector>
#include "Tile.h"

namespace MidasMiner
{
	class Grid
	{
	public:
		Grid();
		~Grid();

		Tile* GetTile(int x, int y);


	private:
		int mWidth;
		int mHeight;
		std::vector< std::vector< Tile * > * > mGrid;
	};
}
