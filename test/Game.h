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
	Game();					//�����֎~
	Game(const Game&);		//�R�s�[�֎~
	void operator=(const Game&)const;	//����֎~
public:

	static Game& Instance() {
		static Game instance;
		return instance;
	}
	~Game();

	///�d�͂�Ԃ�
	float GetGravity() const;

	///�������n
	void Initialize();

	///���Ƀ��[�v
	void Run();

	///�㏈��
	void Terminate();
};

