#pragma once

#include <vector>
#include "InputListener.h"
#include "Grid.h"
#include <king/Engine.h>

namespace MidasMiner
{
	class InputListener;

	class Input
	{
	public:
		Input() {};
		Input(King::Engine& engine);
		~Input();

		void Notify(float x, float y);
		void Attach(InputListener& listener);
		void Update();
	private:
		std::vector<InputListener*> mListeners;
		King::Engine* mEngine;
	};
}