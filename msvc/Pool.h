#ifndef POOL_H_
#define POOL_H_

#pragma once

#include "Renderer.h"
#include "Tile.h"
#include <iostream>
#include <queue>

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

#endif // POOL_H_