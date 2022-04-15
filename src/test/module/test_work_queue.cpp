#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "utils/work_queue.h"

TEST(WorkQueue, concurrent_op) {
  burglar::WorkQueue<int> work_queue;
  std::vector<int> v;

  std::thread t1([&] {
    for (int i = 0; i < 500; i++) {
      work_queue.push(i);
    }
  });

  std::thread t2([&] {
    for (int i = 500; i < 1000; i++) {
      work_queue.push(i);
    }
  });

  std::thread t3([&] {
    for (int i = 0; i < 1000; i++) {
      v.push_back(work_queue.pop());
    }
  });

  t1.join();
  t2.join();
  t3.join();

  std::sort(v.begin(), v.end());

  // check result
  EXPECT_EQ(v[0], 0);
  for (int i = 1; i < 1000; i++)
    EXPECT_EQ(v[i - 1] + 1, v[i]);
}

TEST(WorkQueue, wait_till_not_full) {
  burglar::WorkQueue<int> work_queue(1);
  work_queue.push(1);

  std::thread t1([&] {
    sleep(1);
    std::cout << "ready to pop" << std::endl;
    work_queue.pop();
  });

  std::cout << "push queue" << std::endl;
  work_queue.push(1);

  t1.join();
}

TEST(WorkQueue, wait_till_not_empty) {
  burglar::WorkQueue<int> work_queue;

  std::thread t1([&] {
    sleep(1);
    std::cout << "ready to push" << std::endl;
    work_queue.push(2);
  });

  std::cout << "pop queue" << std::endl;
  int ele = work_queue.pop();
  EXPECT_EQ(ele, 2);

  t1.join();
}