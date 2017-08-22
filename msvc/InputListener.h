#pragma once

#include "Input.h"

namespace MidasMiner
{
	class InputListener
	{
	public:
		virtual ~InputListener();
		virtual void OnMouseDown(float x, float y) = 0;
		virtual void OnMouseUp(float x, float y) = 0;
	};
}