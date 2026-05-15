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
    std::string sourceDir = argv[1];
    std::string backupDir = argv[2]; 
    int threadCount = std::stoi(argv[3]);

    std::cout << "Source Directory: " << sourceDir << std::endl;
    std::cout << "Backup Directory: " << backupDir << std::endl;
    std::cout << "Thread Count: " << threadCount << std::endl;


    
    return 0;
}