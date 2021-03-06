#pragma once
#include "Geometry.h"
#include <memory>


class Octopus;
class Player;

class Game
{
private:
	std::shared_ptr<Octopus> octopus;
	std::shared_ptr<Player> player;
	Game();					//生成禁止
	Game(const Game&);		//コピー禁止
	void operator=(const Game&)const;	//代入禁止
public:

	static Game& Instance() {
		static Game instance;
		return instance;
	}
	~Game();

	///重力を返す
	float GetGravity() const;

	///初期化系
	void Initialize();

	///中にループ
	void Run();

	///後処理
	void Terminate();
};

