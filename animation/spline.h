#ifndef PGR_SEM_COPAKOND_SPLINE_H
#define PGR_SEM_COPAKOND_SPLINE_H
#include <functional>
#include <vector>
#include "../pgr-portable.h"

namespace copakond {
    /** @brief Base class for parameterized spline animations */
    class Spline {
    protected:
        float t = 0.0f; /**< Current continuous time of the spline animation */
        float duration; /**< Total time to complete one full spline loop */
        size_t pointsCount; /**< Number of control points */
        bool hasDerivative;
        bool paused = false;

        bool hasFunctionVector = false;
        bool hasFunctionVectorDerivative = false;
        std::function<void(glm::vec3)> applyVector; /**< Callback function to apply calculated position */
        std::function<void(glm::vec3)> applyVectorDerivative; /**< Callback function to apply calculated tangent */

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

        /**
         * @brief Updates spline state and calculates new vectors based on time.
         * @param deltaTime Time elapsed since the last frame.
         */
        void update(float deltaTime);
        void pause() { paused = true; }
        void unpause() { paused = false; }
        void reset() { t = 0.0f; }
    };
}

#endif //PGR_SEM_COPAKOND_SPLINE_H
