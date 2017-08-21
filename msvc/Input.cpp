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
		for (std::vector<InputListener*>::iterator iter = mListeners.begin(); iter != mListeners.end(); iter++)
		{
			(*iter)->OnMouseDown(x, y);
		}
	}

	void Input::Attach(InputListener& listener)
	{
		mListeners.push_back(&listener);
	}

	void Input::Update()
	{
		if (mEngine->GetMouseButtonDown())
		{
			Notify(mEngine->GetMouseX(), mEngine->GetMouseY());
		}
	}
}