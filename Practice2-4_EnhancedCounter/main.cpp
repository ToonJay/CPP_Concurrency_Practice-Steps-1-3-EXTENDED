#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

int counter{0};

std::mutex m;

void increment_counter() {
	for (size_t i = 0; i < 1000000; i++) {
		std::lock_guard<std::mutex> lg(m);
		counter++;
	}
}

int main() {
	auto start = std::chrono::steady_clock::now();
	std::vector<std::thread> threads;

	for (size_t i = 0; i < 10; i++) {
		threads.emplace_back(std::thread(increment_counter));
	}

	for (std::thread& t : threads) {
		t.join();
	}

	auto stop = std::chrono::steady_clock::now();
	std::cout << "Counter: " << counter << std::endl;
	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << std::endl;

	return 0;
}