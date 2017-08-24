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
		mSwapOrder = 0;
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
			ExecuteMatch(RetrieveMatch(firstSelect, minLongToMatch));
			ExecuteMatch(RetrieveMatch(secondSelect, minLongToMatch));
			std::cout << "ExecuteMatch" << std::endl;
			mGrid->PrintGrid();
			CollapseBoard();
			std::cout << "CollapseBoard" << std::endl;
			mGrid->PrintGrid();
			SummonNewTiles();
			std::cout << "SummonNewTiles" << std::endl;
			mGrid->PrintGrid();
			while (CheckAutoMatch(minLongToMatch))
			{
				ExecuteAutoMatch(minLongToMatch);
			}
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
				newVec->back()->SetPosition(j, i);			}
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

		if (comboLength < minLong)
			comboLength = 0;

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

		if (comboLength < minLong)
			comboLength = 0;

		for (int i = cStart; i < cStart + comboLength; i++)
		{
			res.push_back(mGrid->GetTile(t->GetX(), i));
		}

		//Delete duplicate elements
		std::sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());

		return res;
	}

	void Controller::ExecuteMatch(std::vector<Tile*> tiles)
	{
		for (auto a : tiles)
		{
			mGrid->RemoveTile(a->GetX(), a->GetY());
		}
	}

	void Controller::CollapseBoard()
	{
		for (int i = 0; i < mGrid->GetWidth(); i++)
		{
			ReOrganizeColumn(i);
		}
	}

	void Controller::ReOrganizeColumn(int x)
	{
		int count = 0;
		std::vector<int> index;

		for (int i = 0; i<mGrid->GetHeight(); i++)
		{
			mGrid->GetTile(x, i)->SetPosition(x, i);

			if (mGrid->GetTile(x, i)->IsEmpty())
			{
				count++;
				index.push_back(i);
			}
		}

		if (index.size() > 0)
		{
			int howManyWillDrop = index[0];

			for (int i = howManyWillDrop; i > 0; i--)
			{
				mGrid->Swap(*(mGrid->GetTile(x, i - 1)), *(mGrid->GetTile(x, i - 1 + count)));
			}
			mSwapOrder++;
		}
	}

	void Controller::SummonNewTiles()
	{
		FillEmptyTiles();
	}

	void Controller::FillEmptyTiles()
	{
		for (int i = 0; i<mGrid->GetWidth(); i++)
		{
			for (int j = 0; j<mGrid->GetHeight(); j++)
			{
				if (mGrid->GetTile(j, i)->IsEmpty())
				{
					mGrid->AddTile(j, i);
				}
			}
		}
		mSwapOrder++;
	}

	bool Controller::CheckAutoMatch(int minLong)
	{
		for (int i = 0; i < mGrid->GetWidth(); i++)
		{
			for (int j = 0; j < mGrid->GetHeight(); j++)
			{
				if (CheckMatch(mGrid->GetTile(j, i), minLong))
				{
					return true;
				}
			}
		}

		return false;
	}

	void Controller::ExecuteAutoMatch(int minLong)
	{
		for (int i = 0; i < mGrid->GetWidth(); i++)
		{
			for (int j = 0; j < mGrid->GetHeight(); j++)
			{
				if (CheckMatch(mGrid->GetTile(j, i), minLong))
				{
					ExecuteMatch(RetrieveMatch(mGrid->GetTile(j, i), minLong));
					std::cout << "ExecuteAutoMatch at " << j << " " << i << std::endl;
					mGrid->PrintGrid();
					CollapseBoard();
					std::cout << "CollapseBoard  - Auto" << std::endl;
					mGrid->PrintGrid();
					SummonNewTiles();
					std::cout << "SummonNewTiles - Auto" << std::endl;
					mGrid->PrintGrid();
				}
			}
		}
	}
	
	void Controller::SetReadyAllTiles()
	{
		for (int i = 0; i < mGrid->GetHeight(); i++)
		{
			for (int j = 0; j < mGrid->GetWidth(); j++)
			{
				mGrid->GetTile(i, j)->SetReady(true);
			}
		}
	}
}