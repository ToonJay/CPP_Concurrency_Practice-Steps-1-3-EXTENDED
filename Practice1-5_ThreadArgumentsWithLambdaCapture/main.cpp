#include <iostream>
#include <thread>

int main() {
	int x{5};
	int y{11};

	std::cout << "X = " << x << std::endl;
	std::cout << "Y = " << y << std::endl;

	std::thread t1{[&x]() { 
		x += 3; 
		std::cout << "(in lambda) X = " << x << std::endl;
	}};

	std::thread t2{[y]() mutable {
		y *= 2;
		std::cout << "(in lambda) Y = " << y << std::endl;
	}};
	

	t1.join();
	t2.join();

	std::cout << "(after lambda) X = " << x << std::endl;
	std::cout << "(after lambda) Y = " << y << std::endl;

	return 0;
}