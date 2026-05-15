#include <filesystem>

namespace Utils {
    bool fileExists(const std::filesystem::path& path);
    bool isFileDifferent(
        const std::filesystem::path& src,
        const std::filesystem::path&file
    );
    std::filesystem::path makeRelativePath(
        const std::filesystem::path& base,
        const std::filesystem::path& file
    );
}