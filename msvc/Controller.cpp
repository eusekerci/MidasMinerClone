#include "Controller.h"

namespace MidasMiner
{
	Controller::Controller(Input& input, Grid& grid, GridView& view)
	{
		input.Attach(*this);
		mGrid = &grid;
		mView = &view;
	}


	Controller::~Controller()
	{
	}

	void Controller::OnMouseDown(float x, float y)
	{

	}
}