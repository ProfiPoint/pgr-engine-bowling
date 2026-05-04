#include "spline.h"

namespace copakond {
    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector)
    : vector(vector), vectorDerivative(vector) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = false;
        this->hasFunctionVector = false;
        this->hasFunctionVectorDerivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector)
    : vector(vector), vectorDerivative(vector), applyVector(applyVector) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = false;
        this->hasFunctionVector = true;
        this->hasFunctionVectorDerivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vectorDerivative)
    : vector(vector), vectorDerivative(vectorDerivative) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = true;
        this->hasFunctionVector = false;
        this->hasFunctionVectorDerivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector, glm::vec3 &vectorDerivative)
    : vector(vector), vectorDerivative(vectorDerivative), applyVector(applyVector) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = true;
        this->hasFunctionVector = true;
        this->hasFunctionVectorDerivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, std::function<void(glm::vec3)> applyVectorDerivative)
    : vector(vector), vectorDerivative(vector), applyVectorDerivative(applyVectorDerivative) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = true;
        this->hasFunctionVector = false;
        this->hasFunctionVectorDerivative = true;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> applyVector, std::function<void(glm::vec3)> applyVectorDerivative)
    : vector(vector), vectorDerivative(vector), applyVector(applyVector), applyVectorDerivative(applyVectorDerivative) {
        this->duration = duration;
        this->points = points;
        this->pointsCount = points.size();
        this->hasDerivative = true;
        this->hasFunctionVector = true;
        this->hasFunctionVectorDerivative = true;
    }

    void Spline::update(float deltaTime) {
        if (paused || pointsCount == 0) { return; }

        t += deltaTime;
        t = fmod(t, duration);

        float segmentDuration = duration / pointsCount;
        float localT = fmod(t, segmentDuration) / segmentDuration;
        int offsetIndex = floor(t / segmentDuration);

        size_t p0i = (offsetIndex - 1 + pointsCount) % pointsCount;
        size_t p1i = offsetIndex % pointsCount;
        size_t p2i = (offsetIndex + 1) % pointsCount;
        size_t p3i = (offsetIndex + 2) % pointsCount;

        _P0 = points[p0i];
        _P1 = points[p1i];
        _P2 = points[p2i];
        _P3 = points[p3i];

        glm::vec3 normalResult = evaluateNormal(localT);
        if (hasFunctionVector) {
            if (applyVector) { applyVector(normalResult); }
        } else {
            vector = normalResult;
        }

        if (hasDerivative) {
            glm::vec3 derivativeResult = evaluateDerivative(localT);
            if (hasFunctionVectorDerivative) {
                if (applyVectorDerivative) { applyVectorDerivative(derivativeResult); }
            } else {
                vectorDerivative = derivativeResult;
            }
        }
    }
}