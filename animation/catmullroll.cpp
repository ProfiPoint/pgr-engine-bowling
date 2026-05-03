#include "catmullroll.h"

namespace copakond {
    glm::vec3 CatmullRoll::evaluateNormal(float local_t) {
        float t0 = 1.0f;
        float t1 = local_t;
        float t2 = local_t * t1;
        float t3 = local_t * t2;

        glm::vec3 result;
        result  = _P0 * (t3 * -1.0f + t2 * 2.0f + t1 * -1.0f + t0 * 0.0f);
        result += _P1 * (t3 * 3.0f + t2 * -5.0f + t1 * 0.0f + t0 * 2.0f);
        result += _P2 * (t3 * -3.0f + t2 * 4.0f + t1 * 1.0f + t0 * 0.0f);
        result += _P3 * (t3 * 1.0f + t2 * -1.0f + t1 * 0.0f + t0 * 0.0f);
        result /= 2.0f;

        return result;
    }

    glm::vec3 CatmullRoll::evaluateDerivative(float local_t) {
        float t0 = 0.0f;
        float t1 = 1.0f;
        float t2 = 2.0f * local_t;
        float t3 = 3.0f * local_t * local_t;

        glm::vec3 result;
        result  = _P0 * (t3 * -1.0f + t2 * 2.0f + t1 * -1.0f + t0 * 0.0f);
        result += _P1 * (t3 * 3.0f + t2 * -5.0f + t1 * 0.0f + t0 * 2.0f);
        result += _P2 * (t3 * -3.0f + t2 * 4.0f + t1 * 1.0f + t0 * 0.0f);
        result += _P3 * (t3 * 1.0f + t2 * -1.0f + t1 * 0.0f + t0 * 0.0f);
        result /= 2.0f;

        return result;
    }

}