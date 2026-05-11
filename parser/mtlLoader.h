#ifndef PGR_SEM_COPAKOND_MTLLOADER_H
#define PGR_SEM_COPAKOND_MTLLOADER_H

#include <map>
#include <memory>

#include "../geometry/material.h"

namespace copakond {

class MtlLoader {
private:
    std::map<std::string, std::shared_ptr<Material>> _materials;

public:
    /** @brief Parses .mtl files to construct Material objects and load associated textures */
    MtlLoader(std::string fileName);
    std::map<std::string, std::shared_ptr<Material>> getMaterials() { return _materials; }
};

}

#endif //PGR_SEM_COPAKOND_MTLLOADER_H
