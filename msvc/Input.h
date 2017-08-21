#ifndef INPUT_H_
#define INPUT_H_

#pragma once

#include <vector>
#include <king/Engine.h>
#include "Grid.h"
#include "Controller.h"

namespace MidasMiner
{
	class InpusListener;
	class Controller;

	class Input
	{
	public:
		Input() {};
		Input(King::Engine& engine);
		~Input();

		void Notify(float x, float y);
		void Attach(Controller& listener);
		void Update();
	private:
		std::vector<Controller*> mListeners;
		King::Engine* mEngine;
	};
}

#endif // INPUT_H_