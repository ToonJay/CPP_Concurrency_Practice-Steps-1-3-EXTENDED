#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

std::mutex m;
std::vector<std::thread::id> threadIDs;


void print(std::string name) {
	std::lock_guard<std::mutex> lg(m);
	std::cout << "I am Thread " << name << ", my ID is " << std::this_thread::get_id() << std::endl;
	threadIDs.push_back(std::this_thread::get_id());
}

int main() {
	std::thread t1(print, "worker-1");
	std::thread t2(print, "worker-2");
	std::thread t3(print, "worker-3");
	std::thread t4(print, "worker-4");
	std::thread t5(print, "worker-5");

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	std::sort(threadIDs.begin(), threadIDs.end(), [](std::thread::id x, std::thread::id y) {return x < y; });

	for (auto ID : threadIDs) {
		std::cout << ID << std::endl;
	}
}