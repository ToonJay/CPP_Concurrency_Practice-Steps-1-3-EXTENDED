#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;

std::mutex m;

void hello() {
	std::cout << "Thread " << std::this_thread::get_id() << ": started.\n";

	std::cout << "Thread " << std::this_thread::get_id() << ": sleeping.\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread " << std::this_thread::get_id() << ": woke up.\n";

	std::cout << "Thread " << std::this_thread::get_id() << ": attempting to lock.\n";
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "Thread " << std::this_thread::get_id() << ": lock acquired.\n";

		std::cout << "Thread " << std::this_thread::get_id() << ": sleeping.\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "Thread " << std::this_thread::get_id() << ": woke up.\n";
		std::cout << "Thread " << std::this_thread::get_id() << ": lock released.\n";
	}

	std::cout << "Thread " << std::this_thread::get_id() << ": sleeping.\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread " << std::this_thread::get_id() << ": woke up.\n";

	std::cout << "Thread " << std::this_thread::get_id() << ": finished.\n";
}

int main() {
	std::vector<std::thread> threads;

	for (int i = 0; i < 5; i++) {
		threads.emplace_back(std::thread(hello));
	}

	for (std::thread& t : threads) {
		t.join();
	}
}