#ifndef RAYTRACER_THREADPOOL_H
#define RAYTRACER_THREADPOOL_H
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>
#include <memory> // WICHTIG für std::make_shared

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

    // Template-Implementierung MUSS im Header stehen
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        
        auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto encapsulated_ptr =
            std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        // Geändert: std::result_of_t ist in C++26 entfernt, nutze stattdessen decltype
        std::future<decltype(f(args...))> future_object = encapsulated_ptr->get_future();
        
        {
            std::unique_lock<std::mutex> lock(mutex);
            queue.emplace([encapsulated_ptr]() {
                (*encapsulated_ptr)(); // execute the fx
            });
        }
        cv.notify_one();
        return future_object;
    }

    ThreadPool(ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};

#endif //RAYTRACER_THREADPOOL_H