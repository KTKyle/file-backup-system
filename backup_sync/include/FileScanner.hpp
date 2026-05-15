#include <vector>
#include <filesystem>

class FileScanner {
    public:
        FileScanner();

        std::vector<std::filesystem::path> scan(
            const std::filesystem::path& root
        );

    private:
        void scanDirectory(
            const std::filesystem::path& current,
            std::vector<std::filesystem::path>& files
        );
};