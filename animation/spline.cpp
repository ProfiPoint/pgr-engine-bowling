#include "spline.h"

namespace copakond {
    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector)
    : vector(vector), vector_derivative(vector) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = false;
        this->has_function_vector = false;
        this->has_function_vector_derivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector)
    : vector(vector), vector_derivative(vector), apply_vector(apply_vector) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = false;
        this->has_function_vector = true;
        this->has_function_vector_derivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vector_derivative)
    : vector(vector), vector_derivative(vector_derivative) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = true;
        this->has_function_vector = false;
        this->has_function_vector_derivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector, glm::vec3 &vector_derivative)
    : vector(vector), vector_derivative(vector_derivative), apply_vector(apply_vector) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = true;
        this->has_function_vector = true;
        this->has_function_vector_derivative = false;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, std::function<void(glm::vec3)> apply_vector_derivative)
    : vector(vector), vector_derivative(vector), apply_vector_derivative(apply_vector_derivative) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = true;
        this->has_function_vector = false;
        this->has_function_vector_derivative = true;
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, std::function<void(glm::vec3)> apply_vector, std::function<void(glm::vec3)> apply_vector_derivative)
    : vector(vector), vector_derivative(vector), apply_vector(apply_vector), apply_vector_derivative(apply_vector_derivative) {
        this->duration = duration;
        this->points = points;
        this->points_count = points.size();
        this->has_derivative = true;
        this->has_function_vector = true;
        this->has_function_vector_derivative = true;
    }

    void Spline::update(float delta_time) {
        if (paused || points_count == 0) { return; }

        t += delta_time;
        t = fmod(t, duration);

        float segment_duration = duration / points_count;
        float localT = fmod(t, segment_duration) / segment_duration;
        int offset_index = floor(t / segment_duration);

        size_t p0_i = (offset_index - 1 + points_count) % points_count;
        size_t p1_i = offset_index % points_count;
        size_t p2_i = (offset_index + 1) % points_count;
        size_t p3_i = (offset_index + 2) % points_count;

        _P0 = points[p0_i];
        _P1 = points[p1_i];
        _P2 = points[p2_i];
        _P3 = points[p3_i];

        glm::vec3 normal_result = evaluateNormal(localT);
        if (has_function_vector) {
            if (apply_vector) { apply_vector(normal_result); }
        } else {
            vector = normal_result;
        }

        if (has_derivative) {
            glm::vec3 derivative_result = evaluateDerivative(localT);
            if (has_function_vector_derivative) {
                if (apply_vector_derivative) { apply_vector_derivative(derivative_result); }
            } else {
                vector_derivative = derivative_result;
            }
        }
    }
}