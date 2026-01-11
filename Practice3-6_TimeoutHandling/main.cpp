#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

int task() {
	int i{1};

	for (size_t j = 0; j < 10; j++) {
		std::this_thread::sleep_for(10ms);
		i *= 2;
	}

	return i;
}

int main() {
	std::future<int> f(std::async(std::launch::async, task));

	auto status = f.wait_for(500ms);

	if (status == std::future_status::ready) {
		std::cout << "The result is: " << f.get() << std::endl;
	} else if (status == std::future_status::timeout){
		std::cout << "timeout!" << std::endl;
	}

	return 0;
}