#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <utility>

void compute_value(std::vector<std::promise<int>> promises) {
	int i{0};
	for (std::promise<int>& p : promises) {
		p.set_value(++i);
	}
}

int main() {
	std::vector<std::promise<int>> promises;
	std::vector<std::future<int>> futures;
	for (size_t i = 0; i < 5; i++) {
		std::promise<int> p;
		std::future<int> f = p.get_future();
		promises.push_back(std::move(p));
		futures.push_back(std::move(f));
	}

	std::thread t(compute_value, std::move(promises));

	for (auto& f : futures) {
		std::cout << f.get() << std::endl;
	}

	t.join();
}