#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::vector<int> numbers;
std::mutex m;
int global_counter{0};

void push_number() {
	for (size_t i = 0; i < 10000000; i++) {
		std::lock_guard<std::mutex> lg(m); // without lock, 2 data race conditions
		numbers.push_back(++global_counter);
	}
}

int main() {
	auto start{std::chrono::steady_clock::now()};
	//numbers.reserve(100000000); // prevents cost from memory re-allocation
	std::vector<std::thread> threads;

	for (size_t i = 0; i < 10; i++) {
		threads.emplace_back(std::thread(push_number));
	}

	for (std::thread& t : threads) {
		t.join();
	}

	auto stop{std::chrono::steady_clock::now()};

	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << std::endl;
	return 0;
}