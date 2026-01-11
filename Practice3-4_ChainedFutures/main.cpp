#include <iostream>
#include <future>
#include <utility>

int task2(std::future<int> f) {

	return f.get() * 2;
}

int main() {
	std::future<int> f1(std::async(std::launch::async, []() {return 5 + 2; }));
	std::future<int> f2(std::async(std::launch::async, task2, std::move(f1)));

	std::cout << f2.get() << std::endl;

	return 0;
}