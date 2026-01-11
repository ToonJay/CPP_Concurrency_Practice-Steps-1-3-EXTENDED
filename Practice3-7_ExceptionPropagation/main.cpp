#include <iostream>
#include <future>

int task() {
	throw "error";
}

int main() {
	std::future<int> f(std::async(std::launch::async, task));

	try {
		std::cout << f.get() << std::endl;
	}
	catch (...) {
		std::cout << "error thrown" << std::endl;
	}

	return 0;
}