#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#pragma once

#include "Grid.h"
#include "GridView.h"
#include "InputListener.h"

namespace MidasMiner
{
	class GridView;
	class Input;
	
	class Controller : public InputListener
	{

	public:
		Controller() {};
		Controller(Input& input, Grid& grid, GridView& view);
		~Controller();
		void OnMouseDown(float x, float y);
		void OnMouseUp(float x, float y);
		void OnTileSelected(Tile& t);
		void ResetSelections();
		void OnFirstSelected(Tile& t);
		void OnSecondSelected(Tile& t);

	private:
		Grid* mGrid;
		GridView* mView;
		Tile* firstSelect;
		Tile* secondSelect;
	};
}

#endif // CONTROLLER_H_