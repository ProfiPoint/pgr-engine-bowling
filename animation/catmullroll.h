#ifndef PGR_SEM_COPAKOND_CATMULLROLL_H
#define PGR_SEM_COPAKOND_CATMULLROLL_H

#include "spline.h"

namespace copakond {
    /** @brief Catmull-Rom spline implementation */
    class CatmullRoll : public Spline {
    protected:
        /** * @brief Evaluates the exact point on the Catmull-Rom curve segment.
         * @param localT Normalized time (0.0 to 1.0) within the segment.
         */
        glm::vec3 evaluateNormal(float localT) override;

        /** * @brief Evaluates the tangent/derivative vector on the curve.
         * @param localT Normalized time (0.0 to 1.0) within the segment.
         */
        glm::vec3 evaluateDerivative(float localT) override;

    public:
        using Spline::Spline;
    };
}

#endif //PGR_SEM_COPAKOND_CATMULLROLL_H
