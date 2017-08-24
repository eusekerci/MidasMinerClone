#include "ScoreManager.h"

namespace MidasMiner
{
	ScoreManager::ScoreManager()
	{

	}

	ScoreManager::ScoreManager(Controller& controller, King::Engine& engine)
	{
		mController = &controller;
		mEngine = &engine;
		mInitialTime = 60.0f;
		mTime = 0.0f;
		mScoreSheet = 
		{
			{THREE_LINE, 300},
			{FOUR_LINE, 400},
			{FIVE_LINE, 500},
			{CROSS_LINE, 500}
		};
	}

	ScoreManager::~ScoreManager()
	{
	}

	void ScoreManager::Init()
	{
		mTime= mInitialTime;
		mScore = 0;
		mController->Attach(dynamic_cast<MatchListener*>(this));
	}

	void ScoreManager::Update()
	{
		mTime -= mEngine->GetLastFrameSeconds();
	}

	int ScoreManager::GetScore()
	{
		return mScore;
	}

	void ScoreManager::AddScore(int s)
	{
		mScore += s;
	}

	int ScoreManager::GetTime()
	{
		return static_cast<int>(mTime);
	}

	float ScoreManager::GetExactTime()
	{
		return mTime;
	}

	void ScoreManager::OnMatch(MatchTypes type, int x, int y)
	{
		AddScore(mScoreSheet[type]);
	}
}