#include <iostream>
#include <memory>

struct Sword {
	Sword() = default;
	Sword(const Sword& Original) {
		std::cout << "Copying Sword\n";
	}
};

struct Player {
	Player() : Weapon{std::make_unique<Sword>()} {}
	Player(const Player& Original) : Weapon{std::make_unique<Sword>(*Original.Weapon)} {
		std::cout << "Copying Player\n";
	}

	std::unique_ptr<Sword> Weapon;
};

int main() {
	Player PlayerOne;
	Player PlayerTwo{PlayerOne};

	if (PlayerOne.Weapon != PlayerTwo.Weapon) {
		std::cout << "Players are NOT sharing "
					 "the same weapon";
	}
}
