#pragma once

#include "Input.h"

namespace MidasMiner
{
	class InputListener
	{
	public:
		virtual void OnMouseDown(float x, float y) = 0;
	};
}