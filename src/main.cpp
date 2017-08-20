#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include "../msvc/Grid.h"
#include "../msvc/Tile.h"
#include "../msvc/PoolContainer.h"

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

	}

	void Start() {
		mEngine.Start(*this);
		mGrid = Grid();
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);

		for(int i=0; i<8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (mGrid.GetTile(i, j) != nullptr)
				{
					mEngine.Render(static_cast<King::Engine::Texture>(static_cast<int>(mGrid.GetTile(i, j)->GetColor())+1), 325.0f + j * 44.0f, 100.0f + i * 44.0f);
				}
			}
		}
	}

private:
	King::Engine mEngine;
	Grid mGrid;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	//ExampleGame game;
	MidasMinerGame game;
	game.Start();

	return 0;
}