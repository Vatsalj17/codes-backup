#include <iostream>
using namespace std;

class Character {
   public:
    Character(string name) {
        this->name = name;
    }
	virtual void Act(Character* Target) {
		cout << "Character Acting\n";
	}
    string name;
};

class Goblin : public Character {
   public:
    Goblin(string name) : Character(name) {}
	void Act(Character* Target) {
		cout << "Goblin Acting\n";
        cout << "Name: " << Target->name << endl;
	}
};

class Dragon : public Character {
   public:
    Dragon(string name) : Character(name) {}
	void Act(Character* Target) {
		cout << "Dragon Acting\n";
        cout << "Name: " << Target->name << endl;
	}
};

void Battle(Character* A, Character* B) {
	A->Act(B);
	B->Act(A);
}

int main() {
	Goblin A("A");
	Dragon B("B");
	Battle(&A, &B);
}
