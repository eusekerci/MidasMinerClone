#include "Controller.h"

namespace MidasMiner
{
	Controller::Controller(Input& input, Grid& grid, GridView& view)
	{
		mGrid = &grid;
		mView = &view;

		firstSelect = NULL;
		secondSelect = NULL;
	}


	Controller::~Controller()
	{
	}

	void Controller::OnMouseDown(float x, float y)
	{
		if (mView->IsTileClicked(x, y))
		{
			OnTileSelected(*(mView->GetTileClicked(x,y)));
		}
	}

	void Controller::OnMouseUp(float x, float y)
	{

	}

	void Controller::OnTileSelected(Tile& t)
	{
		if (firstSelect != NULL)
		{
			if (*firstSelect != t && firstSelect->IsAdjacent(&t))
			{
				OnSecondSelected(t);
			}
			else
			{
				OnFirstSelected(t);
			}
		}
		else
		{
			OnFirstSelected(t);
		}
	}

	void Controller::ResetSelections()
	{
		firstSelect = NULL;
		secondSelect = NULL;
		mView->OnResetSelection();
	}

	void Controller::OnFirstSelected(Tile& t)
	{
		firstSelect = &t;
		mView->OnFirstSelected(t);
	}

	void Controller::OnSecondSelected(Tile& t)
	{
		secondSelect = &t;
	}
}