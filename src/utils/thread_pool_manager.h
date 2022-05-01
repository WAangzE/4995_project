#pragma once
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "utils/work_queue.h"

namespace burglar {
class ThreadPoolManager {
 public:
  ThreadPoolManager(int thread_pool_size)
      : thread_pool_size_(thread_pool_size),
        threads_(std::vector<std::thread>(thread_pool_size)),
        shut_down_(false),
        work_queue_(std::make_shared<WorkQueue<std::function<void()>>>()){};
  ThreadPoolManager(const ThreadPoolManager&) = delete;
  ThreadPoolManager(ThreadPoolManager&&) = delete;
  ThreadPoolManager& operator=(const ThreadPoolManager&) = delete;
  ThreadPoolManager& operator=(const ThreadPoolManager&&) = delete;
  void init() {
    for (int i = 0; i < thread_pool_size_; i++) {
      threads_[i] = std::thread(ThreadWorker(this, i));
    }
  }
  void shut_down() {
    shut_down_ = true;
    for (int i = 0; i < thread_pool_size_; i++) {
      if (threads_[i].joinable()) {
        threads_[i].join();
      }
    }
  }

  template <typename F, typename... Args>
  auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
    std::function<void()> wrapper_func = [task_ptr]() { (*task_ptr)(); };
    work_queue_->push(wrapper_func);
    return task_ptr->get_future();
  }

 private:
  class ThreadWorker {
   public:
    ThreadWorker(ThreadPoolManager* pool, const int id) : pool_(pool), id_(id) {}
    void operator()() {
      while (!pool_->shut_down_) {
        auto func = pool_->work_queue_->pop();
        func();
      }
    }

   private:
    int id_;
    ThreadPoolManager* pool_;
  };

 private:
  int thread_pool_size_;
  bool shut_down_;
  std::shared_ptr<WorkQueue<std::function<void()>>> work_queue_;
  std::vector<std::thread> threads_;
};

}  // namespace burglar