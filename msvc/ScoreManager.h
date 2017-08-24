#pragma once

#include "MatchListener.h"
#include "Controller.h"
#include <king\Engine.h>
#include <map>
#include <string>

namespace MidasMiner
{
	class ScoreManager : public MatchListener
	{
	public:
		ScoreManager();
		ScoreManager(Controller& controller, King::Engine& engine);
		~ScoreManager();
		void Init();
		void Update();
		int GetScore();
		void AddScore(int s);
		int GetTime();
		float GetExactTime();
		void OnMatch(MatchTypes type, int x, int y);
	private:
		King::Engine* mEngine;
		int mScore;
		float mInitialTime;
		float mTime;
		std::map<MatchTypes, int> mScoreSheet;
	};
}