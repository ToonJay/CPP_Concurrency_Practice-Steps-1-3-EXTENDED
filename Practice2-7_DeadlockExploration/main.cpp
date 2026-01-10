#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex m1;
std::mutex m2;

void task1() {
	std::lock_guard<std::mutex> lg1(m1);
	std::lock_guard<std::mutex> lg2(m2);
	std::this_thread::sleep_for(400ms);
}

void task2() {
	std::lock_guard<std::mutex> lg2(m2);
	std::this_thread::sleep_for(800ms);
}

void task3() {
	auto deadline = std::chrono::steady_clock::now() + 500ms;
	while (std::chrono::steady_clock::now() < deadline) {
		std::lock_guard<std::mutex> lg2(m2);
		if (m1.try_lock()) {
			std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
			for (size_t i = 0; i < 10; i++) {
				std::cout << "TASK 3: LOCKS ACQUIRED!" << std::endl;
			}
			break;
		}
		std::this_thread::sleep_for(50ms);
	}
}

int main() {
	std::thread t1(task1);
	std::thread t2(task2);
	std::thread t3(task3);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}