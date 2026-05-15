/*
Be able to:
Parse CLI arguments
Initialize system
Start backup process
*/
#include <iostream>
#include <string>
#include <fstream>

#include "../include/FileCopier.hpp"
#include "../include/FileScanner.hpp"
#include "../include/Logger.hpp"
#include "../include/ThreadPool.hpp"
#include "../include/Utils.hpp"

int main(int argc, char* argv[])
{
    if(argc != 4) // Verifies number of cli args
    {
        std::cout << "Error: Wrong number of arguments!" << std::endl;
        std::cout << "Usage: ./backup_tool <source_dir> <backup_dir> <thread_count>" << std::endl;
        return 1;
    }
    std::filesystem::path sourceDir = argv[1];
    std::filesystem::path backupDir = argv[2];
    int threadCount = std::stoi(argv[3]);

    std::cout << "Source Directory: " << sourceDir << std::endl;
    std::cout << "Backup Directory: " << backupDir << std::endl;
    std::cout << "Thread Count: " << threadCount << std::endl;

    FileScanner scanner;
    std::vector<std::filesystem::path> files = scanner.scan(sourceDir);

    if(files.empty())
    {
        std::cout << "No Files found.\n";
        return 0;
    }

    ThreadPool pool(threadCount);
    pool.start();

    for(const auto& file : files)
    {
        if(!Utils::fileExists(file))
        {
            continue;
        }

        std::filesystem::path relative = Utils::makeRelativePath(sourceDir, file);
        std::filesystem::path dest = std::filesystem::path(backupDir) / relative;

        Job job;
        job.source = file;
        job.destination = dest;

        pool.addJob(job);
    }

    pool.wait();
    std::cout << "Backup Complete.\n";
    return 0;
}