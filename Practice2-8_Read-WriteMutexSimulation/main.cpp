#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

std::vector<int> numbers;
int num{0};

std::shared_mutex sm;

void read() {
	std::this_thread::sleep_for(300ms);
	std::shared_lock<std::shared_mutex> sl(sm);
	for (size_t i = 0; i < numbers.size(); i++) {
		std::cout << numbers[i] << std::endl;
	}
}

void write() {
	while (num < 10000) {
		std::lock_guard<std::shared_mutex> lg(sm);
		numbers.push_back(++num);
	}
}

int main() {
	std::thread wt(write);
	std::vector<std::thread> readers;

	for (size_t i = 0; i < 10; i++) {
		readers.emplace_back(std::thread(read));
	}

	wt.join();

	for (std::thread& rt : readers) {
		rt.join();
	}

	return 0;
}