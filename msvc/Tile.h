#pragma once

namespace MidasMiner
{
	class Tile
	{
	public:
		enum TileColor
		{
			COLOR_BLUE,
			COLOR_GREEN,
			COLOR_PURPLE,
			COLOR_RED,
			COLOR_YELLOW
		};

		Tile();
		~Tile();
		Tile(int x, int y, TileColor color);

		bool IsAdjacent(Tile* newTile);
		bool IsEqual(Tile* tile);
		bool operator==(const Tile& t);

		TileColor GetColor();
		int GetX();
		int GetY();
		void SetPosition(int x, int y);

	private:
		int mX;
		int mY;
		Tile::TileColor mColor;
	};
}