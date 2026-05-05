#ifndef PGR_SEM_COPAKOND_IMAGELABEL_H
#define PGR_SEM_COPAKOND_IMAGELABEL_H
#include "imageSequenceLabel.h"

namespace copakond {
    class ImageLabel : public ImageSequenceLabel {
    public:
        ImageLabel(const std::string& imagePath);
        ImageLabel(const std::string& imagePath, std::shared_ptr<Material> material);
    };
}

#endif //PGR_SEM_COPAKOND_IMAGELABEL_H
