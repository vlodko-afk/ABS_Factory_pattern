#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

struct FileInfo {
    std::string name{};
    std::string type{};
    std::string size{};
    fs::file_time_type modified{};
};


class SearchFileInfo
{
private:
    // знаходження розміру папки
    std::uintmax_t getFolderSize(const fs::path& folderPath);

public:
    SearchFileInfo() = default;
    ~SearchFileInfo() = default;

    std::vector<FileInfo> all_files_info{};

    // інформація про файли
    void parth_informations(std::string path);
};