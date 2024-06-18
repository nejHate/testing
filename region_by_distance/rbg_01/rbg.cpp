#include <iostream>
#include <vector>
#include <random>

auto get_random_number(int max){
  static std::random_device rd;
	static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, max);
	return dis(gen);
}

int main(){
  return 0;
  
}
