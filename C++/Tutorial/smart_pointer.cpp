#include <iostream>
#include <memory>

class Character {
   public:
	std::string Name;
	Character(std::string Name = "Frodo") : Name{Name} {
		std::cout << "Creating " << Name << '\n';
	}

	~Character() {
		std::cout << "Deleting " << Name << '\n';
	}
};

int main() {
	std::unique_ptr<int> Pointer{ std::make_unique<int>(42) };

	auto FrodoPointer{std::make_unique<Character>("Frodo")};
	std::cout << "Logging " << (*FrodoPointer).Name << "\n\n";
	auto GandalfPointer{std::make_unique<Character>("Gandalf")};
	std::cout << "Logging " << GandalfPointer->Name << "\n\n";
}
