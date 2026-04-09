#ifndef PGR_SEM_COPAKOND_SHADER_H
#define PGR_SEM_COPAKOND_SHADER_H

#include "pgr.h"
#include "../meshes/mesh.h"
#include "../geometry/camera.h"

namespace copakond {
    class Shader {
    protected:
        GLuint _shaderProgram;

        GLint _modelUID; // model matrix uniform index;
        GLint _viewUID; // view matrix uniform index;
        GLint _projectionUID; // projection matrix uniform index;
        GLint _pvmUID; // PVM matrix uniform index;

        glm::mat4 _viewM;
        glm::mat4 _projectionM;

    public:
        Shader();

        virtual GLuint init(std::string vertShaderLocation, std::string fragShaderLocation);
        virtual void update(Camera &camera, int winWidth, int winHeight);
        virtual void draw(Mesh &mesh);
    };
}


#endif //PGR_SEM_COPAKOND_SHADER_H