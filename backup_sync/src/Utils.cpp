#include "../include/Utils.hpp"

namespace Utils 
{
    bool fileExists(const std::filesystem::path& path)
    {
        return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
    }

    bool isFileDifferent(const std::filesystem::path& src, const std::filesystem::path& file)
    {
        if(!std::filesystem::exists(file))
        {
            return true;
        }

        auto srcSize = std::filesystem::file_size(src);
        auto fileSize = std::filesystem::file_size(file);
        if(srcSize != fileSize)
        {
            return true;
        }

        auto srcTime = std::filesystem::last_write_time(src);
        auto fileTime = std::filesystem::last_write_time(file);
        return srcTime != fileTime;
    }

    std::filesystem::path makeRelativePath(const std::filesystem::path& base, const std::filesystem::path& file)
    {
        return std::filesystem::relative(file, base);
    }
}