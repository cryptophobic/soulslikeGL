#include "init.h"
#include <filesystem>
#include <boost/algorithm/string/replace.hpp>

namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    render::App::start(argc, argv);
    return 0;
}
