#include <iostream>
#include <thread>
#include <chrono>

class thread_guard {
private:
	std::thread& t;

public:
	explicit thread_guard(std::thread& t) : t{t} {};

	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

void hello() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "What's up, doc?" << std::endl;
}

void oops() {
	try {
		throw "error";
	}
	catch (...) {
		std::cout << "Some error" << std::endl;
	}
}

int main() {
	std::thread t1(hello);
	std::thread t2(std::move(t1));
	std::thread t3(oops);

	thread_guard tg1(t1);
	thread_guard tg2(t2);
	thread_guard tg3(t3);

	return 0;
}