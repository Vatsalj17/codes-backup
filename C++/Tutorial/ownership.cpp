#include <iostream>
#include <memory>
#include <utility>

void TakeOwnership(std::unique_ptr<int> Num) {
	std::cout << "TakeOwnership function now owns the pointer.\n";
	std::cout << "Value: " << *Num << '\n';
}

int main() {
	auto Number{std::make_unique<int>(42)};
	std::cout << "main function owns the pointer.\n";

	TakeOwnership(std::move(Number));

	// Number is now in a "moved-from" state
	if (Number == nullptr) {
		std::cout << "Number no longer owns any object.";
	}
}
