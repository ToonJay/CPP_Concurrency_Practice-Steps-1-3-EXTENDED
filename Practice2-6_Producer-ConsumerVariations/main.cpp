#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> num_q;
int num{0};

std::mutex m;
std::condition_variable cond_num;

const int POISON = -1;


void produce_num() {
	while (true) {
		{
			std::lock_guard<std::mutex> lg(m);
			if (num >= 10000) {
				num_q.push(POISON);
				cond_num.notify_one();
				break;
			}
			num_q.push(++num);
			std::cout << "Produced " << num << std::endl;
		}
		cond_num.notify_one();
	}
}

void consume_num() {
	int n;
	while (true) {
		std::unique_lock<std::mutex> ul(m);
		cond_num.wait(ul, []() { return !num_q.empty(); });
		n = num_q.front();
		num_q.pop();
		if (n == POISON) {
			break;
		}
		std::cout << "Consumed " << n << std::endl;
	}
}

int main() {
	std::vector<std::thread> producers;
	std::vector<std::thread> consumers;
	
	for (size_t i = 0; i < 5; i++) {
		producers.push_back(std::thread(produce_num));
		consumers.push_back(std::thread(consume_num));
	}

	for (std::thread& t : producers) {
		t.join();
	}

	for (std::thread& t : consumers) {
		t.join();
	}

	return 0;
}