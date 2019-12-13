#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t poolSize) : pool_is_active(true)
{
   for(size_t i = 0; i < poolSize;++i)
   {
      threads.emplace_back([this]()
                              {
                                    while (pool_is_active == true)//solving and sleeping
                                    {
                                       std::unique_lock<std::mutex> lock(mutex_);//one thread gets owns mutex,others are blocked(sleeping)

                                       if (tasks.empty())
                                       {
                                          queue_is_empty_.wait(lock);//blocking is no tasks
                                       } 
                                       else 
                                       {
                                          task cur_task = tasks.front();//get next task
                                          tasks.pop();//delete task
                                          lock.unlock();//unlocking: mutex is free now
                                          cur_task();
                                       }
                                    }
                              });// sleeping threads 
   }
}


ThreadPool::~ThreadPool()
{
   pool_is_active = false;
   queue_is_empty_.notify_all();
   for (size_t i = 0; i < threads.size(); i++) {
      threads[i].join();
   }   
}
