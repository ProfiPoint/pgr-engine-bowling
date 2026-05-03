#include "bezier.h"

namespace copakond {

    glm::vec3 Bezier::evaluateNormal(float localT) {
        float u = 1.0f - localT;
        float tt = localT * localT;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * localT;

        glm::vec3 result = uuu * _P0;
        result += 3.0f * uu * localT * _P1;
        result += 3.0f * u * tt * _P2;
        result += ttt * _P3;

        return result;
    }

    glm::vec3 Bezier::evaluateDerivative(float localT) {
        float u = 1.0f - localT;
        float uu = u * u;
        float tt = localT * localT;

        glm::vec3 result = 3.0f * uu * (_P1 - _P0);
        result += 6.0f * u * localT * (_P2 - _P1);
        result += 3.0f * tt * (_P3 - _P2);

        return result;
    }

}