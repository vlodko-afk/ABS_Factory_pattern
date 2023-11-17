#include "SearchFileInfo.h"

// розмір папки
std::uintmax_t SearchFileInfo::getFolderSize(const fs::path& folderPath)
{
    std::uintmax_t totalSize = 0;

    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            totalSize += fs::file_size(entry);
        }
    }
    return totalSize;
}


//збирання інформації про файли
void SearchFileInfo::parth_informations(std::string path)
{
    for (const auto& file : fs::recursive_directory_iterator(path)) {
        FileInfo InfoFile;
        const auto& path_file = file.path();
        InfoFile.name = path_file.filename().string();
        if (fs::is_directory(file)) {
            std::uintmax_t folder_size = getFolderSize(path_file);
            InfoFile.size = std::to_string(folder_size) + "(байт)";
        }
        else {
            InfoFile.size = std::to_string(fs::file_size(path_file)) + "(байт)";
        }
        InfoFile.type = fs::is_directory(file) ? "folder" : path_file.extension().string();
        const auto ftime = fs::last_write_time(path_file);
        InfoFile.modified = ftime;
        all_files_info.push_back(InfoFile);
    }
}