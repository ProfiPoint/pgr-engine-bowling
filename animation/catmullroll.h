#ifndef PGR_SEM_COPAKOND_CATMULLROLL_H
#define PGR_SEM_COPAKOND_CATMULLROLL_H

#include "spline.h"

namespace copakond {
    class CatmullRoll : public Spline {
    protected:
        glm::vec3 evaluateNormal(float localT) override;
        glm::vec3 evaluateDerivative(float localT) override;

    public:
        using Spline::Spline;
    };
}

#endif //PGR_SEM_COPAKOND_CATMULLROLL_H
