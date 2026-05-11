#ifndef PGR_SEM_COPAKOND_BEZIER_H
#define PGR_SEM_COPAKOND_BEZIER_H

#include "spline.h"

namespace copakond {
    /** @brief Bezier curve spline implementation */
    class Bezier : public Spline {
    protected:
        /** * @brief Evaluates the exact point on the Bezier curve segment.
         * @param localT Normalized time (0.0 to 1.0) within the segment.
         */
        glm::vec3 evaluateNormal(float localT) override;

        /** * @brief Evaluates the tangent/derivative vector on the Bezier curve.
         * @param localT Normalized time (0.0 to 1.0) within the segment.
         */
        glm::vec3 evaluateDerivative(float localT) override;

    public:
        using Spline::Spline;
    };
}

#endif //PGR_SEM_COPAKOND_BEZIER_H
