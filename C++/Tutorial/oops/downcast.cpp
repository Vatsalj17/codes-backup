#include <iostream>
using namespace std;

class Character {
   public:
	Character(string Name) : mName{Name} {}
	string GetName() { return mName; }
    virtual ~Character() = default;

   private:
	string mName;
};

class Goblin : public Character {
   public:
	Goblin(string Name) : Character{Name} {}

	void Enrage() {
		cout << "Getting Angry!";
		Damage += 5;
	}

   private:
	int Damage{10};
};

void Act(Character* Enemy) {
    Goblin* Goblinptr{dynamic_cast<Goblin*>(Enemy)};
	cout << Enemy->GetName() << " Acting\n";
    // static_cast<Goblin*>(Enemy)->Enrage();
    if (Goblinptr) cout << "This was Goblin\n";
    else cout << "This was not Goblin\n";
}

int main() {
	Goblin Bonker{"Bonker"};
    Character Dragon{"Dave"};
	Act(&Dragon);
    Act(&Bonker);
}
