#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#pragma once

#include "Grid.h"
#include "GridView.h"
#include "InputListener.h"
#include "MatchNotifier.h"
#include "MatchListener.h"
#include <vector>
#include <algorithm>

namespace MidasMiner
{
	class GridView;
	class Input;
	class MatchListener;
	class MatchNotifier;

	enum MatchTypes
	{
		THREE_LINE,
		FOUR_LINE,
		FIVE_LINE,
		CROSS_LINE,
		INVALID_MATCH
	};
	
	class Controller : public InputListener, public MatchNotifier
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

		void Init();
		void Update();
		bool Swap();
		
		bool CheckMatch(Tile* t, int minLong);
		std::vector<Tile*> RetrieveMatch(Tile* t, int minLong);
		MatchTypes GetMatchType(std::vector<Tile*> tiles);

		void ExecuteMatch(std::vector<Tile*> tiles);
		void CollapseBoard();
		void ReOrganizeColumn(int x);
		void SummonNewTiles();
		void FillEmptyTiles();
		bool CheckAutoMatch(int minLong);
		void ExecuteAutoMatch(int minLong);
		void SetReadyAllTiles();

		void OnMatchNotify(MatchTypes type, int x, int y);
		void Attach(MatchListener* listener);
		void Detach(MatchListener* listener);

	private:
		Grid* mGrid;
		GridView* mView;
		
		Tile* firstSelect;
		Tile* secondSelect;
		bool isSelectionActive;
		int minLongToMatch;
		int mSwapOrder;
		bool mouseUp;
	};
}

#endif // CONTROLLER_H_