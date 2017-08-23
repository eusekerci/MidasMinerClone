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
		bool IsSameColor(Tile* tile);
		bool IsSameColor(TileColor color);
		bool operator==(const Tile& t);
		bool operator!=(const Tile& t);

		TileColor GetColor();
		int GetX();
		int GetY();
		bool IsReady();
		void SetReady(bool r);
		void SetPosition(int x, int y);

	private:
		int mX;
		int mY;
		bool mIsReady;
		Tile::TileColor mColor;
	};
}