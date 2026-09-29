//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_THREADPOOL_H
#define RAYTRACER_THREADPOOL_H
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<std::function<void()>> queue;
    void worker();
    bool stop;

public:
    ThreadPool(std::size_t nr_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

    ThreadPool(ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};


#endif //RAYTRACER_THREADPOOL_H
