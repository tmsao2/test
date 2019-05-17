#include "Game.h"
#include <DxLib.h>
#include "Octopus.h"
#include "Player.h"
#include "Peripheral.h"

const int screen_size_x = 1024;
const int screen_size_y = 512;

Game::Game()
{
}

void Game::operator=(const Game &) const
{
}


Game::~Game()
{
}

float Game::GetGravity() const
{
	return 0.5f;
}


void Game::Initialize()
{
	DxLib::SetGraphMode(screen_size_x, screen_size_y, 32);
	DxLib::SetMainWindowText("test");
	DxLib::ChangeWindowMode(true);
	if (DxLib::DxLib_Init() == -1) {
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	octopus = std::make_shared<Octopus>();
	player = std::make_shared<Player>();
}

void Game::Run()
{
	Peripheral p;
	while (ProcessMessage() == 0) {
		if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}
		p.Update();
		player->Update(p);
		DxLib::ClsDrawScreen();
		octopus->Update(player->GetPos());
		player->Draw();
		octopus->Draw();
		DxLib::ScreenFlip();
	}
}

void Game::Terminate()
{
	DxLib::DxLib_End();
}
