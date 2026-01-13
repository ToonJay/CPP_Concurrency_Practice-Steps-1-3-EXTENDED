#include <iostream>
#include <thread>
#include <future>
#include <utility>

void thread_a(std::promise<int> p, std::future<int> f) {
	std::cout << "The answer to Thread A is: " << f.get() << std::endl;
	p.set_value(20);
}

void thread_b(std::promise<int> p, std::future<int> f) {
	p.set_value(5);
	std::cout << "The answer to Thread B is: " << f.get() << std::endl;
}

int main() {
	std::promise<int> p1;
	std::future<int> f1(p1.get_future());
	std::promise<int> p2;
	std::future<int> f2(p2.get_future());

	std::thread t_a(thread_a,std::move(p2), std::move(f1));
	std::thread t_b(thread_b, std::move(p1), std::move(f2));

	t_a.join();
	t_b.join();

	return 0;
}