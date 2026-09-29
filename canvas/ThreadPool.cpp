//
// Created by tobi on 29.09.26.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t nr_workers) {
    stop = false;
    for (auto i{ 0 }; i < nr_workers; i++) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        stop = true;
    }

    cv.notify_all();
    for (auto& worker : workers) {
        worker.join();
    }
}


void ThreadPool::worker() {
    for (;;) {
        std::function<void()> cur_task;
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this]() {
                return stop || !queue.empty();
            });

            if (stop && queue.empty())
                break;
            if (queue.empty())
                continue;

            cur_task = queue.front();
            queue.pop();
            // grab the fx from queue
        }
        cur_task();
    }
}

template<typename F, typename... Args>
inline auto ThreadPool::enqueue(F&& f, Args&&... args)
-> std::future<decltype(f(args...))> {
    auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto encapsulated_ptr =
        std::make_shared<std::packaged_task<decltype(f(args...))()>>
        (func);

    std::future<std::result_of_t<F(Args...)>> future_object = encapsulated_ptr->get_future();
    {
        std::unique_lock<std::mutex> lock(mutex);
        queue.emplace([encapsulated_ptr]() {
            (*encapsulated_ptr)(); // execute the fx
            });
    }
    cv.notify_one();
    return future_object;
}
