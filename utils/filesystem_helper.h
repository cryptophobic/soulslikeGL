//
// Created by dima on 14.08.22.
//

#ifndef SOULSLIKEGL_FILESYSTEM_HELPER_H
#define SOULSLIKEGL_FILESYSTEM_HELPER_H

#include <string>
#include <filesystem>
#include <boost/algorithm/string.hpp>

namespace fs = std::filesystem;


static std::string root;

class FileSystem
{

public:
    static std::string getPath(const std::string& path)
    {
        return root + std::string("/") + path;
    }

    static void setApplicationPath(std::string path) {
        boost::replace_all(path,"./", "");
        const fs::path fullApplicationPath = fs::absolute(fs::path(path));
        root = fullApplicationPath.parent_path().parent_path();
    }
};


#endif //SOULSLIKEGL_FILESYSTEM_HELPER_H
