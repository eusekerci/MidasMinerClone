#ifndef MATCHLISTENER_H_
#define MATCHLISTENER_H_

#pragma once

#include "Controller.h"

namespace MidasMiner
{
	enum MatchTypes;
	class Controller;

	class MatchListener
	{
	public:
		virtual void OnMatch(MatchTypes type, int x, int y) = 0;
	protected:
		Controller* mController;
	};
}

#endif //MATCHLISTENER_H_