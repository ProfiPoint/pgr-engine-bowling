#include "imageLabel.h"

namespace copakond {
    // image label is a special case of image sequence label, but paused
    ImageLabel::ImageLabel(const std::string& imagePath) : ImageSequenceLabel(imagePath, 1, 1, 1, 1) {
        _paused = true;
    }
    ImageLabel::ImageLabel(const std::string& imagePath, std::shared_ptr<Material> material) : ImageSequenceLabel(imagePath, 1, 1, 1, 1, material) {
        _paused = true;
    }
}
