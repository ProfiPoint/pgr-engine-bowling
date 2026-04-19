#ifndef PGR_SEM_COPAKOND_MTLLOADER_H
#define PGR_SEM_COPAKOND_MTLLOADER_H

#include <map>

#include "../geometry/material.h"

namespace copakond {

class MtlLoader {
private:
    std::map<std::string, std::shared_ptr<Material>> _materials;

public:
    MtlLoader(std::string fileName);
    std::map<std::string, std::shared_ptr<Material>> getMaterials() { return _materials; }
};

}

#endif //PGR_SEM_COPAKOND_MTLLOADER_H
