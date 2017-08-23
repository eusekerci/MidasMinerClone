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
		Swap();
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
		std::cout << firstSelect->GetColor() << "(" << firstSelect->GetX() << "," << firstSelect->GetY() << ") " << std::endl;
		std::cout << secondSelect->GetColor() << "(" << secondSelect->GetX() << "," << secondSelect->GetY() << ") " << std::endl;

		mGrid->Swap(*firstSelect, *secondSelect);

		std::vector<Tile*> resFirst = CheckMatch(firstSelect);
		std::vector<Tile*> resSecond = CheckMatch(secondSelect);

		//if (resFirst.size() <= 0 && resSecond.size() <= 0)
		//{
		//	mGrid->PrintGrid();

		//	Tile* temp = firstSelect;
		//	mGrid->AddTile(firstSelect->GetX(), firstSelect->GetY(), secondSelect);
		//	mGrid->AddTile(secondSelect->GetX(), secondSelect->GetY(), temp);

		//	mGrid->PrintGrid();

		//	return false;
		//}
		
		ExecuteMatch(resFirst);
		ExecuteMatch(resSecond);

		std::cout << firstSelect->GetColor() << "(" << firstSelect->GetX() << "," << firstSelect->GetY() << ") " << std::endl;
		std::cout << secondSelect->GetColor() << "(" << secondSelect->GetX() << "," << secondSelect->GetY() << ") " << std::endl;

		mGrid->PrintGrid();

		return true;
	}

	std::vector<Tile*> Controller::CheckMatch(Tile * t)
	{
		return std::vector<Tile*>();
	}

	void Controller::ExecuteMatch(std::vector<Tile*> tiles)
	{
	}

	void Controller::SummonNewTiles(std::vector<Tile*> tiles)
	{
	}
}