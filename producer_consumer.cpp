#include <bits/stdc++.h>
using namespace std;

const int BUFFER_SIZE = 5;

class SharedBuffer {
private:
    queue<int> buffer;
    mutex mutex;
    condition_variable bufferNotEmpty;
    condition_variable bufferNotFull;

public:
    void produce(int data) {
        unique_lock<std::mutex> lock(mutex);
        bufferNotFull.wait(lock, [this] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(data);
        cout << "Produced: " << data << ", Buffer Size: " << buffer.size() << "\n";
        bufferNotEmpty.notify_all();
    }

    int consume() {
        unique_lock<std::mutex> lock(mutex);
        bufferNotEmpty.wait(lock, [this] { return !buffer.empty(); });

        int data = buffer.front();
        buffer.pop();
        cout << "Consumed: " << data << ", Buffer Size: " << buffer.size() << "\n";
        bufferNotFull.notify_all();

        return data;
    }
};

void producer(SharedBuffer& buffer, int producerID) {
    for (int i = 0; i < 10; ++i) {
        buffer.produce(i);
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void consumer(SharedBuffer& buffer, int consumerID) {
    for (int i = 0; i < 10; ++i) {
        int data = buffer.consume();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    SharedBuffer buffer;
    thread producerThread(producer,ref(buffer), 1);
    thread consumerThread(consumer,ref(buffer), 1);
    producerThread.join();
    consumerThread.join();
    this_thread::sleep_for(chrono::seconds(2));

    return 0;
}
