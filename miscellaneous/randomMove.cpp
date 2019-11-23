#include <random>
#include <string>
#include <vector>
#include <iostream>

std::string randomMove() {

	std::vector<std::string> move(7);
    move[0] = "left";
    move[1] = "right";
    move[2] = "fwd";
    move[3] = "leftfwd";
    move[4] = "rightfwd";
    move[5] = "jump";
    move[6] = "back";

    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 6); // Define the range 

    int rIndex = distr(eng);

	return move[rIndex];
}

int main() {

	for(int i = 0; i < 10; i++) {
	std::cout << randomMove() << std::endl;
	}

	return 0;
}