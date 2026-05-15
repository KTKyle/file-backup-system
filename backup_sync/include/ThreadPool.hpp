#include <filesystem>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>

struct Job {
    std::filesystem::path source;
    std::filesystem::path destination;
};

class ThreadPool {
    public:
        ThreadPool(int numThreads);
        ~ThreadPool();

        void addJob(const Job& job);
        void start();
        void wait();

        private:
            int numThreads;
            void workerThread();
            std::vector<std::thread> workers;
            std::queue<Job> jobs;
            std::mutex queueMutex;
            std::condition_variable cv;
            bool stop;
};