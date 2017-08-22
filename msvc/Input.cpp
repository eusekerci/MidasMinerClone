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
			a->OnMouseDown(x, y);
		}
	}

	void Input::OnMouseUpNotify(float x, float y)
	{
		for (auto a : mListeners)
		{
			a->OnMouseUp(x, y);
		}
	}

	void Input::Attach(InputListener* listener)
	{
		InputListener * newListener = listener;
		mListeners.push_back(newListener);
	}

	void Input::Detach(InputListener* listener)
	{
		for (auto a : mListeners)
		{
			if (a == listener)
			{
				mListeners.erase(std::remove(mListeners.begin(), mListeners.end(), listener), mListeners.end());
			}
		}
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