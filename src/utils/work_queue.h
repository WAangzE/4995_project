#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace burglar {

/**
 * thread-safe queue
 */
template <typename T>
class WorkQueue {
 public:
  WorkQueue() : capacity_(10000) {}

  explicit WorkQueue(int capacity) { capacity_ = capacity; }

  int size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  void push(const T& item) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.size() == capacity_)
      full_cond_.wait(lock, [&] { return queue_.size() < capacity_; });
    queue_.push(item);
    if (queue_.size() == 1) {
      empty_cond_.notify_one();
    }
  }

  const T& pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty())
      empty_cond_.wait(lock, [&] { return !queue_.empty(); });
    const T& item = queue_.front();
    queue_.pop();
    if (queue_.size() == capacity_ - 1)
      full_cond_.notify_one();
    return item;
  }

  const T& front() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty())
      empty_cond_.wait(lock, [&] { return !queue_.empty(); });
    return queue_.front();
  }

 private:
  std::queue<T> queue_;
  int capacity_;
  std::mutex mutex_;
  std::condition_variable full_cond_, empty_cond_;
};
}  // namespace burglar
