#include "Input.h"

namespace MidasMiner
{
	Input::Input(King::Engine& engine)
	{
		mEngine = &engine;
	}

	Input::~Input()
	{
	}

	void Input::Notify(float x, float y)
	{
		for (auto a : mListeners)
		{
			(dynamic_cast<Controller*>(a))->OnMouseDown(x, y);
		}
	}

	void Input::Attach(Controller& listener)
	{
		mListeners.push_back(&listener);
	}

	void Input::Update()
	{
		int a = mListeners.size();
		if (mEngine->GetMouseButtonDown())
		{
			Notify(mEngine->GetMouseX(), mEngine->GetMouseY());
		}
	}
}