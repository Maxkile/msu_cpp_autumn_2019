#pragma once

#include <thread>
#include <future>
#include <queue>
#include <vector>
#include <functional>
#include <memory>
#include <condition_variable>

class ThreadPool
{
public:
    using task = std::function<void()>;//default
    using thread_vector = std::vector<std::thread>;
    using task_queue = std::queue<task>;
    
    explicit ThreadPool(size_t poolSize);

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {

        //copying of a task is deleted
        // std::packaged_task<decltype(func(args...))()> new_task([func, args...]() 
        //                                                     {
        //                                                          return func(args...); 
        //                                                     });
        // tasks.push(std::move(new_task)));

        //using pointer to packeged_task
        auto new_task = std::make_shared<std::packaged_task<decltype(func(args...))()>>([func, args...]() 
                                                                                        {
                                                                                            return func(args...); 
                                                                                        });
        tasks.push([new_task]()
                    {
                        (*new_task)();//push packaged_task func
                    });

        std::unique_lock<std::mutex> lock(mutex_);
        queue_is_empty_.notify_one();//notify one waiting thread to stop waiting (so we will leave .wait(lock)) -> one thread awakens and solves task
        return new_task->get_future();
    }

    ~ThreadPool();

private:
    thread_vector threads;
    task_queue tasks;
    std::mutex mutex_;//shared resource
    std::condition_variable queue_is_empty_;//for notifying
    std::atomic_bool pool_is_active;//one for all
};
