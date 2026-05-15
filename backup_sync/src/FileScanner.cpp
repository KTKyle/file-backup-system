/*
Be able to:
Traverse directory recursively
Return list of files
*/

#include "../include/FileScanner.hpp"

FileScanner::FileScanner(){}

std::vector<std::filesystem::path> FileScanner::scan(const std::filesystem::path& root)
{
    std::vector<std::filesystem::path> results;
    scanDirectory(root, results);
    return results;
}

void FileScanner::scanDirectory(const std::filesystem::path& current, std::vector<std::filesystem::path>& results)
{
    for (const auto& entry : std::filesystem::directory_iterator(current))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            results.push_back(entry.path());
        }
        else if (std::filesystem::is_directory(entry))
        {
            scanDirectory(entry.path(), results);
        }
    }
}