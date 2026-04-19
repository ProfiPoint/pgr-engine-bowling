#ifndef PGR_SEM_COPAKOND_MTLLOADER_H
#define PGR_SEM_COPAKOND_MTLLOADER_H

#include "../geometry/material.h"

namespace copakond {

class MtlLoader {
private:
    std::shared_ptr<Material> _material = std::make_shared<Material>();

public:
    MtlLoader(std::string fileName);
    std::shared_ptr<Material>& material() { return _material; }
};

}

#endif //PGR_SEM_COPAKOND_MTLLOADER_H
