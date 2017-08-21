#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#pragma once

#include "Grid.h"
#include "GridView.h"
#include "InputListener.h"

namespace MidasMiner
{
	class GridView;
	
	class Controller : public InputListener
	{

	public:
		Controller() {};
		Controller(Input& input, Grid& grid, GridView& view);
		~Controller();
		virtual void OnMouseDown(float x, float y);

	private:
		Grid* mGrid;
		GridView* mView;
	};
}

#endif // CONTROLLER_H_