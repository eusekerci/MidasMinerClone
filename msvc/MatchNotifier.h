#ifndef MATCHNOTIFIER_H_
#define MATCHNOTIFIER_H_
#pragma once

#include "Controller.h"

namespace MidasMiner
{
	enum MatchTypes;
	class Controller;
	class MatchListener;

	class MatchNotifier
	{
	public:
		virtual void OnMatchNotify(MatchTypes type, int x, int y) = 0;
		virtual void Attach(MatchListener* listener) = 0;
		virtual void Detach(MatchListener* listener) = 0;
	protected:
		std::vector<MatchListener*> mListeners;
	};
}

#endif