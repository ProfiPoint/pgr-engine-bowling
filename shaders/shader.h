#ifndef PGR_SEM_COPAKOND_SHADER_H
#define PGR_SEM_COPAKOND_SHADER_H

#include "pgr.h"
#include "../meshes/mesh.h"
#include "../geometry/camera.h"
#include "../light/light.h"

namespace copakond {
    class Shader {
    protected:
        GLuint _shaderProgram;

        GLint _modelUID; // model matrix uniform index;
        GLint _viewUID; // view matrix uniform index;
        GLint _projectionUID; // projection matrix uniform index;
        GLint _pvmUID; // PVM matrix uniform index;
        GLint _camPos; // position of camera eye position uniform index;
        GLint _normalMatrix; // correct matrix for non-rigid transform uniform index;

        GLint _ambient;
        GLint _diffuse;
        GLint _specular;
        GLint _shininess;
        GLint _alpha;

        GLint _lightType;
        GLint _lightPos;
        GLint _lightDir;
        GLint _lightAmb;
        GLint _lightDiff;
        GLint _lightSpec;
        GLint _lightRange;
        GLint _lightAngle;
        GLint _lightExponent;
        GLint _lightDim;

        glm::mat4 _viewM; // camera view matrix
        glm::mat4 _projectionM; // perspective projection matrix
        glm::vec3 _position;

    public:
        Shader();

        virtual void setLight(Light *light);

        virtual GLuint init(std::string vertShaderLocation, std::string fragShaderLocation);
        virtual void update(Camera &camera, int winWidth, int winHeight);
        virtual void draw(Mesh &mesh);
    };
}


#endif //PGR_SEM_COPAKOND_SHADER_H
