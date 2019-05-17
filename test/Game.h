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
	Game();					//¶¬‹Ö~
	Game(const Game&);		//ƒRƒs[‹Ö~
	void operator=(const Game&)const;	//‘ã“ü‹Ö~
public:

	static Game& Instance() {
		static Game instance;
		return instance;
	}
	~Game();

	///d—Í‚ğ•Ô‚·
	float GetGravity() const;

	///‰Šú‰»Œn
	void Initialize();

	///’†‚Éƒ‹[ƒv
	void Run();

	///Œãˆ—
	void Terminate();
};

