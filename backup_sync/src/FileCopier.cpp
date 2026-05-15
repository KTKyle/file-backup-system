/*
Be able to:
Copy individual file
Handle directory creation
Return success/failure
*/

#include "../include/FileCopier.hpp"

FileCopier::FileCopier(){}

bool FileCopier::copyFile(const std::filesystem::path& source, const std::filesystem::path& destination)
{
    if(!std::filesystem::exists(source))
    {
        return false;
    }

    std::filesystem::path destDir = destination.parent_path();

    if(!directoryExists(destDir))
    {
        std::filesystem::create_directories(destDir);
    }

     std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
    
     return true;
}

bool FileCopier::directoryExists(const std::filesystem::path& path)
{
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}