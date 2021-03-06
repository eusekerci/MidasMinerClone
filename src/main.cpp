#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include "../msvc/Input.h"
#include "../msvc/Grid.h"
#include "../msvc/Tile.h"
#include "../msvc/GridView.h"
#include "../msvc/Controller.h"
#include "../msvc/PoolContainer.h"
#include "../msvc/ScoreManager.h"

using namespace MidasMiner;

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, mYellowDiamondX(100.0f)
		, mYellowDiamondY(100.0f) {
	}

	void Start() {
		mEngine.Start(*this);
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_GREEN, 650.0f, 100.0f);
		mEngine.Render(King::Engine::TEXTURE_RED, 100.0f, 450.0f);
		mEngine.Render(King::Engine::TEXTURE_BLUE, 650.0f, 450.0f);

		mEngine.Write("Green", 650.0f, 140.0f);
		mEngine.Write("Red", 100.0f, 490.0f);
		mEngine.Write("Blue", 650.0f, 490.0f);

		const char text[] = "This rotates at 5/PI Hz";
		mRotation += mEngine.GetLastFrameSeconds();
		mEngine.Write(text, mEngine.GetWidth() / 2.0f, mEngine.GetHeight() / 2.0f, mRotation * 2.5f);

		if (mEngine.GetMouseButtonDown()) {
			mYellowDiamondX = mEngine.GetMouseX();
			mYellowDiamondY = mEngine.GetMouseY();
		}
		mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);
		mEngine.Write("Click to", mYellowDiamondX, mYellowDiamondY + 40.0f);
		mEngine.Write("move me!", mYellowDiamondX, mYellowDiamondY + 70.0f);
	}

private:
	King::Engine mEngine;
	float mRotation;
	float mYellowDiamondX;
	float mYellowDiamondY;
};

class MidasMinerGame : public King::Updater {
public:

	MidasMinerGame()
		: mEngine("./assets")
	{
		mInput = Input(mEngine);
		mGrid = Grid();
		mView = GridView(mEngine, mGrid, mScoreAndTime);
		mController = Controller(mInput, mGrid, mView);
		mScoreAndTime = ScoreManager(mController, mEngine);
	}

	void Start() {
		mController.Init();
		mView.Init();
		mScoreAndTime.Init();
		mEngine.Start(*this);
	}

	void Update()
	{
		mInput.Update();
		mController.Update();
		mScoreAndTime.Update();
		mView.Update();
	}

private:
	King::Engine mEngine;
	Input mInput;
	Grid mGrid;
	GridView mView;
	Controller mController;
	ScoreManager mScoreAndTime;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	//ExampleGame game;
	MidasMinerGame game;
	game.Start();

	return 0;
}