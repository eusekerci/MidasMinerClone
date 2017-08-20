#pragma once

#include <queue>
#include "Tile.h"

namespace MidasMiner
{
	class Pool
	{
	public:
		Pool(Tile instance, int poolSize);
		~Pool();

		Tile* Get();

		Tile** GetMany(int a);

		void Kill(Tile* t);

		void KillMany(Tile** t);

	private:
		std::queue<Tile*> mPool;
		Tile mInstance;
	};
}