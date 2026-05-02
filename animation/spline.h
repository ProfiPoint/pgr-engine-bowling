#ifndef PGR_SEM_COPAKOND_SPLINE_H
#define PGR_SEM_COPAKOND_SPLINE_H
#include <vector>
#include "../pgr-portable.h"

namespace copakond {
    class Spline {
    private:
        float t = 0.0f;
        float duration;
        size_t points_count;
        bool has_derivative;
        bool paused = false;

        std::vector<glm::vec3> points;
        glm::vec3 &vector;
        glm::vec3 &vector_delta;

        glm::vec3 _P0;
        glm::vec3 _P1;
        glm::vec3 _P2;
        glm::vec3 _P3;
        glm::vec3 _catmullRollNormal(float local_t);
        glm::vec3 _catmullRollDerivative(float local_t);
    public:
        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector);
        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vector_delta); // will also update derivative
        void update(float delta_time);
        void pause() { paused = true; }
        void unpause() { paused = false; }
    };
}

#endif //PGR_SEM_COPAKOND_SPLINE_H
