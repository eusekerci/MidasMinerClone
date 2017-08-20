#include "Pool.h"

namespace MidasMiner
{
	Pool::Pool(Tile instance, int poolSize)
	{
		mInstance = instance;
		mPool = std::queue<Tile *>();
		for (int i = 0; i < poolSize; i++)
		{
			mPool.push(new Tile(mInstance));
		}
	}

	Pool::~Pool()
	{
	}

	Tile* Pool::Get()
	{
		if (mPool.empty())
		{
			return new Tile(mInstance);
		}

		Tile* t = mPool.front();
		mPool.pop();

		return t;
	}

	Tile ** Pool::GetMany(int a)
	{
		Tile** res = new Tile*[a];
		for (int i; i < a; i++)
		{
			res[i] = Get();
		}

		return res;
	}

	void Pool::Kill(Tile * t)
	{
		mPool.push(t);
	}

	void Pool::KillMany(Tile ** t)
	{
		for (int i = 0; i < sizeof(t) / sizeof(Tile*); i++)
		{
			Kill(t[i*sizeof(Tile*)]);
		}
	}

}