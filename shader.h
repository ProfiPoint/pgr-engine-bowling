#ifndef PGR_SEM_COPAKOND_SHADER_H
#define PGR_SEM_COPAKOND_SHADER_H

#include "pgr.h"
#include "camera.h"

namespace copakond {
    class Shader {
    protected:
        GLuint shaderProgram;

        GLint M_unfId; // model matrix uniform index;
        GLint V_unfId; // view matrix uniform index;
        GLint P_unfId; // projection matrix uniform index;
        GLint PVM_unfId; // PVM matrix uniform index;

    public:
        Shader();

        virtual GLuint init(std::string vertShaderLocation, std::string fragShaderLocation);
        virtual void draw(Camera camera, int WIN_WIDTH, int WIN_HEIGHT);
    };
}


#endif //PGR_SEM_COPAKOND_SHADER_H