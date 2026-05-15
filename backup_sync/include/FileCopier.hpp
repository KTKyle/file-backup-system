#include <filesystem>

class FileCopier {
    public: 
        FileCopier();

        bool copyFile(
            const std::filesystem::path& source,
            const std::filesystem::path& destination
        );

    private:
        bool directoryExists(const std::filesystem::path& path);
};