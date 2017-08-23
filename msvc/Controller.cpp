#include "Controller.h"

namespace MidasMiner
{
	Controller::Controller(Input& input, Grid& grid, GridView& view)
	{
		mGrid = &grid;
		mView = &view;

		firstSelect = NULL;
		secondSelect = NULL;
		
		isSelectionActive = true;
		minLongToMatch = 3;
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
		if (!isSelectionActive)
		{
			return;
		}
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
		isSelectionActive = true;
	}

	void Controller::OnFirstSelected(Tile& t)
	{
		firstSelect = &t;
		mView->OnFirstSelected(t);
	}

	void Controller::OnSecondSelected(Tile& t)
	{
		secondSelect = &t;
		isSelectionActive = false;
		if (Swap())
		{

		}
		else
		{

		}
		ResetSelections();
	}

	void Controller::InitBoard()
	{
		std::vector<std::vector< Tile * > *> res;
		for (int i = 0; i < mGrid->GetHeight(); i++)
		{
			std::vector< Tile* > * newVec = new std::vector< Tile* >();
			for (int j = 0; j < mGrid->GetWidth(); j++)
			{
				newVec->push_back(mGrid->RandomTile());
				newVec->back()->SetPosition(j, i);
				mView->SpawnTileTween(*(newVec->back()));
			}
			res.push_back(newVec);
		}

		mGrid->SetGrid(res);
	}

	bool Controller::Swap()
	{
		mGrid->Swap(*firstSelect, *secondSelect);

		if (CheckMatch(firstSelect, 3) || CheckMatch(secondSelect, 3))
		{
			std::cout << "Swap Succeed" << std::endl;
			mGrid->PrintGrid();

			return true;
		}

		//Revert
		mGrid->Swap(*firstSelect, *secondSelect);

		std::cout << "Swap Failed" << std::endl;
		mGrid->PrintGrid();

		return false;
	}

	bool Controller::CheckMatch(Tile * t, int minLong)
	{
		//Check row
		int inStart = t->GetX() - (minLong - 1) >= 0 ? t->GetX() - (minLong - 1) : 0;
		int inEnd = t->GetX() + (minLong - 1) < mGrid->GetWidth() ? t->GetX() + (minLong - 1) : mGrid->GetWidth() - 1;
		int comboLength = 0;
		
		for (int i = inStart; i <= inEnd; i++)
		{
			if (mGrid->GetTile(i, t->GetY())->IsSameColor(t))
			{
				comboLength++;
			}
			else if(comboLength >= minLong)
			{
				return true;
			}
			else
			{
				comboLength = 0;
			}
		}

		if (comboLength >= minLong)
			return true;

		//Check column
		inStart = t->GetY() - (minLong - 1) >= 0 ? t->GetY() - (minLong -1 ) : 0;
		inEnd = t->GetY() + (minLong - 1) < mGrid->GetHeight() ? t->GetY() + (minLong - 1) : mGrid->GetHeight() - 1;
		comboLength = 0;
		
		for (int i = inStart; i <= inEnd; i++)
		{
			if (mGrid->GetTile(t->GetX(), i)->IsSameColor(t))
			{
				comboLength++;
			}
			else if (comboLength >= minLong)
			{
				return true;
			}
			else
			{
				comboLength = 0;
			}
		}

		if (comboLength >= minLong)
			return true;

		return false;
	}

	std::vector<Tile*> Controller::RetrieveMatch(Tile * t, int minLong)
	{
		std::vector<Tile*> res;
		//Check row
		int inStart = t->GetX() - (minLong - 1) >= 0 ? t->GetX() - (minLong - 1) : 0;
		int inEnd = t->GetX() + (minLong - 1) < mGrid->GetWidth() ? t->GetX() + (minLong - 1) : mGrid->GetWidth() - 1;
		int comboLength = 0;
		int cStart = 0;

		for (int i = inStart; i <= inEnd; i++)
		{
			if (mGrid->GetTile(i, t->GetY())->IsSameColor(t))
			{
				if (comboLength == 0)
					cStart = i;
				comboLength++;
			}
			else if (comboLength >= minLong)
			{
				break;
			}
			else
			{
				comboLength = 0;
			}
		}

		for (int i = cStart; i < cStart+comboLength; i++)
		{
			res.push_back(mGrid->GetTile(i, t->GetY()));
		}

		//Check column
		inStart = t->GetY() - (minLong - 1) >= 0 ? t->GetY() - (minLong - 1) : 0;
		inEnd = t->GetY() + (minLong - 1) < mGrid->GetHeight() ? t->GetY() + (minLong - 1) : mGrid->GetHeight() - 1;
		comboLength = 0;

		for (int i = inStart; i <= inEnd; i++)
		{
			if (mGrid->GetTile(t->GetX(), i)->IsSameColor(t))
			{
				if (comboLength == 0)
					cStart = i;
				comboLength++;
			}
			else if (comboLength >= minLong)
			{
				break;
			}
			else
			{
				comboLength = 0;
			}
		}

		for (int i = cStart; i < cStart + comboLength; i++)
		{
			res.push_back(mGrid->GetTile(t->GetX(), i));
		}

		return res;
	}

	void Controller::ExecuteMatch(std::vector<Tile*> tiles)
	{
	}

	void Controller::SummonNewTiles(std::vector<Tile*> tiles)
	{
	}
}