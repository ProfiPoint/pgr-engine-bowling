#include "bezier.h"

namespace copakond {

    glm::vec3 Bezier::evaluateNormal(float local_t) {
        float u = 1.0f - local_t;
        float tt = local_t * local_t;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * local_t;

        glm::vec3 result = uuu * _P0;
        result += 3.0f * uu * local_t * _P1;
        result += 3.0f * u * tt * _P2;
        result += ttt * _P3;

        return result;
    }

    glm::vec3 Bezier::evaluateDerivative(float local_t) {
        float u = 1.0f - local_t;
        float uu = u * u;
        float tt = local_t * local_t;

        glm::vec3 result = 3.0f * uu * (_P1 - _P0);
        result += 6.0f * u * local_t * (_P2 - _P1);
        result += 3.0f * tt * (_P3 - _P2);

        return result;
    }

}