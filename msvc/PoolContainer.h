#ifndef POOLCONTAINER_H_
#define POOLCONTAINER_H_

#pragma once

#include "Pool.h"

namespace MidasMiner
{
	static Pool BlueTilePole = Pool(Tile(0, 0, Tile::COLOR_BLUE), 65);
	static Pool GreenTilePole = Pool(Tile(0, 0, Tile::COLOR_GREEN), 65);
	static Pool PurpleTilePole = Pool(Tile(0, 0, Tile::COLOR_PURPLE), 65);
	static Pool YellowTilePole = Pool(Tile(0, 0, Tile::COLOR_YELLOW), 65);
	static Pool RedTilePole = Pool(Tile(0, 0, Tile::COLOR_RED), 65);

	static Pool* TilePools[] = { &BlueTilePole, &GreenTilePole, &PurpleTilePole, &YellowTilePole, &RedTilePole };
}

#endif //POOLCONTAINER_H_