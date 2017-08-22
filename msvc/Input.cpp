#include "Input.h"

namespace MidasMiner
{
	Input::Input(King::Engine& engine)
	{
		mEngine = &engine;
		onMouseButtonUp = false;
	}

	Input::~Input()
	{
	}

	void Input::OnMouseClickNotify(float x, float y)
	{
		for (auto a : mListeners)
		{
			(dynamic_cast<Controller*>(a))->OnMouseDown(x, y);
		}
	}

	void Input::OnMouseUpNotify(float x, float y)
	{
		for (auto a : mListeners)
		{
			(dynamic_cast<Controller*>(a))->OnMouseUp(x, y);
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
			onMouseButtonUp = true;
			OnMouseClickNotify(mEngine->GetMouseX(), mEngine->GetMouseY());
		}
		else if(onMouseButtonUp)
		{
			onMouseButtonUp = false;
			OnMouseUpNotify(mEngine->GetMouseX(), mEngine->GetMouseY());
		}
	}
}