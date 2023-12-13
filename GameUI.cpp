#include "GameUI.h"
#include "Game.h"
#include "GameBoard.h"
#include "Button.h"
#include <functional>

GameUI::GameUI(Game* game) : UIScreen(game)
							,mGameBoard(nullptr)
							,mHeaderDims(Vector2(0.0f, 0.0f))
							,mState(Easy)
{
	game->SetGameBoard(new GameBoard(mGame, 10, Vector2(9.0, 9.0)));
	mGameBoard = game->GetGameBoard();
	mHeaderDims.x = (9 * 32);
	mHeaderDims.y = (2 * 32);
	mGameBoard->SetPosition(Vector2(0.0f, mHeaderDims.y));
	mGame->ResizeWindow(Vector2(mHeaderDims.x, (2 * 32) + (9 * 32)));
	GenerateButtons();
}

GameUI::~GameUI()
{
}

void GameUI::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = mHeaderDims.x;
	r.h = mHeaderDims.y;

	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderFillRect(renderer, &r);

	if (!mButtons.empty())
	{
		for (auto const& b : mButtons)
		{
			if (b->GetHighlighted())
			{
				b->Draw(b->GetSelected(), renderer);
			}
			else
			{
				b->Draw(b->GetUnSelected(), renderer);
			}
		}
	}
}

void GameUI::GenerateButtons()
{
	// Reset Button
	mFont = mGame->GetFont("Assets/Caviar_Dreams_Bold.ttf");
	mButtonSelected = mGame->GetTexture("Assets/Sad_face.png");
	mButtonUnSelected = mGame->GetTexture("Assets/Happy_face.png");
	AddButton("", [this]() {return this->ButtonResetGame(); });
	mButtons[0]->SetPosition(Vector2(mHeaderDims.x / 2, mHeaderDims.y - 32));
	mButtons[0]->SetDimension(Vector2(64, 64));
	mButtons[0]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	mButtonSelected = mGame->GetTexture("Assets/unclick_hover.png");
	mButtonUnSelected = mGame->GetTexture("Assets/unclicked_tile.png");
	AddButton("Easy", [this]() {return this->SetEasy(); });
	mButtons[1]->SetDimension(Vector2(64, 20));
	mButtons[1]->SetPosition(Vector2(32, 10));
	mButtons[1]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	AddButton("Medium", [this]() {return this->SetMedium(); });
	mButtons[2]->SetDimension(Vector2(64, 20));
	mButtons[2]->SetPosition(Vector2(32, 30));
	mButtons[2]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	AddButton("Hard", [this]() {return this->SetHard(); });
	mButtons[3]->SetDimension(Vector2(64, 20));
	mButtons[3]->SetPosition(Vector2(32, 50));
	mButtons[3]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	
}

void GameUI::ButtonResetGame()
{
	SDL_Log("Clicked");
	if (mState == Easy)
	{
		mGameBoard->ResetGame(10, Vector2(9.0, 9.0));
		mHeaderDims.x = (9 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((9 * 32) / 2, mHeaderDims.y - 32));
	}
	if (mState == Medium)
	{
		mGameBoard->ResetGame(25, Vector2(15.0, 15.0));
		mHeaderDims.x = (15 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((15 * 32) / 2, mHeaderDims.y - 32));
	}
	if (mState == Hard)
	{
		mGameBoard->ResetGame(50, Vector2(18.0, 18.0));
		mHeaderDims.x = (18 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((18 * 32) / 2, mHeaderDims.y - 32));
	}
}

void GameUI::SetEasy()
{
	Vector2 dims(9.0, 9.0);
	SetHeaderDims(Vector2(dims.y * 32, 2 * 32));
	SetState(GameUI::Easy);
}

void GameUI::SetMedium()
{
	Vector2 dims(15.0, 15.0);
	SetState(GameUI::Medium);
	SetHeaderDims(Vector2(dims.x * 32, 2 * 32));
}

void GameUI::SetHard()
{
	Vector2 dims(18.0, 18.0);
	SetState(GameUI::Hard);
	SetHeaderDims(Vector2(dims.y * 32, 2 * 32));
}

void GameUI::SetState(State state)
{
	mState = state;
	ButtonResetGame();
}
