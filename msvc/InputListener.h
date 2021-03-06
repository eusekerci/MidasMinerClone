#pragma once

#include "Input.h"

namespace MidasMiner
{
	class Input;

	class InputListener
	{
	public:
		virtual void OnMouseDown(float x, float y) = 0;
		virtual void OnMouseUp(float x, float y) = 0;
	protected:
		Input* mInput;
	};
}