#ifndef PGR_SEM_COPAKOND_CATMULLROLL_H
#define PGR_SEM_COPAKOND_CATMULLROLL_H

#include "spline.h"

namespace copakond {
    class CatmullRoll : public Spline {
    protected:
        glm::vec3 evaluateNormal(float local_t) override;
        glm::vec3 evaluateDerivative(float local_t) override;

    public:
        using Spline::Spline;
    };
}

#endif //PGR_SEM_COPAKOND_CATMULLROLL_H
