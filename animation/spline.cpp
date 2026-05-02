#include "spline.h"

namespace copakond {
    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector) : vector(vector), vector_delta(vector) {
        this->duration = duration;
        this->points = points;
        this->has_derivative = false;
        this->points_count = points.size();
    }

    Spline::Spline(float duration, std::vector<glm::vec3> &points, glm::vec3 &vector, glm::vec3 &vector_delta) : vector(vector), vector_delta(vector_delta) {
        this->duration = duration;
        this->points = points;
        this->has_derivative = true;
        this->points_count = points.size();
    }

    // Catmull Roll Spline
    glm::vec3 Spline::_catmullRollNormal(float local_t) {
        float t0 = 1;
        float t1 = local_t;
        float t2 = local_t * t1;
        float t3 = local_t * t2;

        glm::vec3 result;
        result  = _P0 * (t3 * -1 + t2 * 2 + t1 * -1 + t0 * 0);
        result += _P1 * (t3 * 3 + t2 * -5 + t1 * 0 + t0 * 2);
        result += _P2 * (t3 * -3 + t2 * 4 + t1 * 1 + t0 * 0);
        result += _P3 * (t3 * 1 + t2 * -1 + t1 * 0 + t0 * 0);
        result /= 2;

        return result;
    }

    glm::vec3 Spline::_catmullRollDerivative(float local_t) {
        float t0 = 0;
        float t1 = 1;
        float t2 = 2 * local_t;
        float t3 = 3 * local_t * local_t;

        glm::vec3 result;
        result  = _P0 * (t3 * -1 + t2 * 2 + t1 * -1 + t0 * 0);
        result += _P1 * (t3 * 3 + t2 * -5 + t1 * 0 + t0 * 2);
        result += _P2 * (t3 * -3 + t2 * 4 + t1 * 1 + t0 * 0);
        result += _P3 * (t3 * 1 + t2 * -1 + t1 * 0 + t0 * 0);
        result /= 2;

        return result;
    }

    void Spline::update(float delta_time) {
        if (paused) { return; }

        t += delta_time;
        t = fmod(t, duration);

        float time_per_segment = duration / points_count;
        float local_t = fmod(t, time_per_segment) / time_per_segment;
        int offset_index = floor(t / time_per_segment);

        size_t p0_i = (offset_index-1 + points_count) % points_count;
        size_t p1_i = (offset_index+0) % points_count;
        size_t p2_i = (offset_index+1) % points_count;
        size_t p3_i = (offset_index+2) % points_count;

        _P0 = points[p0_i];
        _P1 = points[p1_i];
        _P2 = points[p2_i];
        _P3 = points[p3_i];

        vector = _catmullRollNormal(local_t);
        if (has_derivative) { vector_delta = _catmullRollDerivative(local_t); }
    }
}
