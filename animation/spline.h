#ifndef PGR_SEM_COPAKOND_SPLINE_H
#define PGR_SEM_COPAKOND_SPLINE_H
#include <functional>
#include <vector>
#include "../pgr-portable.h"

namespace copakond {
    class Spline {
    protected:
        float t = 0.0f;
        float duration;
        size_t points_count;
        bool has_derivative;
        bool paused = false;

        bool has_function_vector = false;
        bool has_function_vector_derivative = false;
        std::function<void(glm::vec3)> apply_vector;
        std::function<void(glm::vec3)> apply_vector_derivative;

        std::vector<glm::vec3> points;
        glm::vec3 &vector;
        glm::vec3 &vector_derivative;

        glm::vec3 _P0;
        glm::vec3 _P1;
        glm::vec3 _P2;
        glm::vec3 _P3;

        virtual glm::vec3 evaluateNormal(float local_t) = 0; // = 0 no body implementation
        virtual glm::vec3 evaluateDerivative(float local_t) = 0;
    public:
        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector);

        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vector_derivative);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector, glm::vec3 &vector_derivative);
        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, std::function<void(glm::vec3)> apply_vector_derivative);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector, std::function<void(glm::vec3)> apply_vector_derivative);

        void update(float delta_time);
        void pause() { paused = true; }
        void unpause() { paused = false; }
        void reset() { t = 0.0f; }
    };
}

#endif //PGR_SEM_COPAKOND_SPLINE_H
