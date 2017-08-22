#ifndef INPUT_H_
#define INPUT_H_

#pragma once

#include <vector>
#include <king/Engine.h>
#include "Grid.h"
#include "InputListener.h"

namespace MidasMiner
{
	class InputListener;

	class Input
	{
	public:
		Input() {};
		Input(King::Engine& engine);
		~Input();

		void OnMouseClickNotify(float x, float y);
		void OnMouseUpNotify(float x, float y);
		void Attach(InputListener* listener);
		void Detach(InputListener* listener);
		void Update();
	private:
		std::vector<InputListener*> mListeners;
		King::Engine* mEngine;
		bool onMouseButtonUp;
	};
}

#endif // INPUT_H_