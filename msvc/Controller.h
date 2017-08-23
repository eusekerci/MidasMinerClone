#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#pragma once

#include "Grid.h"
#include "GridView.h"
#include "InputListener.h"
#include <vector>
#include <algorithm>

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

		void InitBoard();
		bool Swap();
		
		bool CheckMatch(Tile* t, int minLong);
		std::vector<Tile*> RetrieveMatch(Tile* t, int minLong);

		void ExecuteMatch(std::vector<Tile*> tiles);
		void CollapseBoard();
		void SummonNewTiles();
		bool CheckAutoMatch(int minLong);
		void ExecuteAutoMatch(int minLong);
		void SetReadyAllTiles();

	private:
		Grid* mGrid;
		GridView* mView;
		Tile* firstSelect;
		Tile* secondSelect;
		bool isSelectionActive;
		int minLongToMatch;
	};
}

#endif // CONTROLLER_H_