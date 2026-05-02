#ifndef PGR_SEM_COPAKOND_FOG_H
#define PGR_SEM_COPAKOND_FOG_H

#include "../pgr-portable.h"

namespace copakond {
    class Fog {
    public:
        int enabled = false;
        float start;
        float end;
        glm::vec4 color;

        Fog(float start, float end, glm::vec4 color) {
            this->start = start;
            this->end = end;
            this->color = color;
            this->enabled = true;
        }

        Fog() {}; // if fog is disabled
    };
}

#endif //PGR_SEM_COPAKOND_FOG_H
