#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class Tqueue {
    private:
    std::queue<T> queue;
    std::condition_variable spop;
    std::mutex mq;
    public:
    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mq);
        queue.push(item);
        spop.notify_one();
    }
    void push(T&& item) {
        std::unique_lock<std::mutex> lock(mq);
        queue.push(std::move(item));
        spop.notify_one();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(mq);
        spop.wait(lock, [this] {return !queue.empty();});
        T item = queue.front();
        queue.pop();
        return item;
    }
};