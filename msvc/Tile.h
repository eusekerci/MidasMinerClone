#pragma once

namespace MidasMiner
{
	class Tile
	{
	public:
		enum TileType
		{
			BASIC,
			POWERUP,
		};

		Tile();
		~Tile();
		Tile(TileType t, int x, int y);

		bool IsAdjacent(Tile* newTile);
		bool IsEqual(Tile* tile);
		bool operator==(const Tile& t);

	private:
		int mX;
		int mY;
		TileType mType;
	};
}