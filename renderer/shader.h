#ifndef PGR_SEM_COPAKOND_SHADER_H
#define PGR_SEM_COPAKOND_SHADER_H

#include "pgr.h"
#include "../geometry/camera.h"

namespace copakond {
    class Shader {
    protected:
        GLuint shaderProgram;

        GLint modelUID; // model matrix uniform index;
        GLint viewUID; // view matrix uniform index;
        GLint projectionUID; // projection matrix uniform index;
        GLint pvmUID; // PVM matrix uniform index;

    public:
        Shader();

        virtual GLuint init(std::string vertShaderLocation, std::string fragShaderLocation);
        virtual void draw(Camera &camera, int WIN_WIDTH, int WIN_HEIGHT);
    };
}


#endif //PGR_SEM_COPAKOND_SHADER_H