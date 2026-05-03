#ifndef PGR_SEM_COPAKOND_BEZIER_H
#define PGR_SEM_COPAKOND_BEZIER_H

#include "spline.h"

namespace copakond {
    class Bezier : public Spline {
    protected:
        glm::vec3 evaluateNormal(float localT) override;
        glm::vec3 evaluateDerivative(float localT) override;

    public:
        using Spline::Spline;
    };
}

#endif //PGR_SEM_COPAKOND_BEZIER_H
