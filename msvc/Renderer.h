#pragma once

#include <king\Engine.h>

namespace MidasMiner
{
	class Renderer
	{
	public:
		struct RenderValues
		{
			King::Engine::Texture Texture;
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
			float Rotation;
		};

		virtual RenderValues GetRenderValues(float anchorX, float anchorY, float tick) = 0;
	protected:
		RenderValues mRenderValues;
	};
}