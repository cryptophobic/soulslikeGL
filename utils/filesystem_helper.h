//
// Created by dima on 14.08.22.
//

#ifndef SOULSLIKEGL_FILESYSTEM_HELPER_H
#define SOULSLIKEGL_FILESYSTEM_HELPER_H

#include <string>
#include <filesystem>
#include <boost/algorithm/string.hpp>

namespace fs = std::filesystem;

class FileSystemHelper
{

public:
    static std::string getPath(const std::string& path);
    static void setApplicationPath(std::string path);

private:
    static std::string root;
};


#endif //SOULSLIKEGL_FILESYSTEM_HELPER_H
