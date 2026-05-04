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
        size_t pointsCount;
        bool hasDerivative;
        bool paused = false;

        bool hasFunctionVector = false;
        bool hasFunctionVectorDerivative = false;
        std::function<void(glm::vec3)> applyVector;
        std::function<void(glm::vec3)> applyVectorDerivative;

        std::vector<glm::vec3> points;
        glm::vec3 &vector;
        glm::vec3 &vectorDerivative;

        glm::vec3 _P0;
        glm::vec3 _P1;
        glm::vec3 _P2;
        glm::vec3 _P3;

        virtual glm::vec3 evaluateNormal(float localT) = 0; // = 0 no body implementation
        virtual glm::vec3 evaluateDerivative(float localT) = 0;
    public:
        virtual ~Spline() = default;

        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector);

        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vectorDerivative);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector, glm::vec3 &vectorDerivative);
        Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, std::function<void(glm::vec3)> applyVectorDerivative);
        Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector, std::function<void(glm::vec3)> applyVectorDerivative);

        void update(float deltaTime);
        void pause() { paused = true; }
        void unpause() { paused = false; }
        void reset() { t = 0.0f; }
    };
}

#endif //PGR_SEM_COPAKOND_SPLINE_H
