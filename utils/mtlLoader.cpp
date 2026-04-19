#include "mtlLoader.h"

#include <fstream>

namespace copakond {
    MtlLoader::MtlLoader(std::string fileName) {
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".mtl") {
            _material = nullptr;
            return;
        }

        std::ifstream file(fileName);
        if (!file.is_open()) {
            _material = nullptr;
            return;
        }
    }
}
