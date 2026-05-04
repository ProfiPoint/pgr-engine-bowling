#ifndef PGR_SEM_COPAKOND_SHADER_H
#define PGR_SEM_COPAKOND_SHADER_H

#define WORLD_AMBIENT glm::vec3(0.25f, 0.25f, 0.25f)

#include "../pgr-portable.h"
#include "../meshes/mesh.h"
#include "../geometry/camera.h"
#include "../light/light.h"

namespace copakond {
    class Shader {
    protected:
        GLuint _shaderProgram = 0;

        GLuint _worldAmbientUID = 0;

        GLint _modelUID = 0; // model matrix uniform index;
        GLint _viewUID = 0; // view matrix uniform index;
        GLint _projectionUID = 0; // projection matrix uniform index;
        GLint _pvmUID = 0; // PVM matrix uniform index;
        GLint _camPos = 0; // position of camera eye position uniform index;
        GLint _normalMatrix = 0; // correct matrix for non-rigid transform uniform index;

        GLint _fogEnabled = 0;
        GLint _fogStart = 0;
        GLint _fogEnd = 0;
        GLint _fogColor = 0;

        GLint _ambient = 0;
        GLint _diffuse = 0;
        GLint _specular = 0;
        GLint _shininess = 0;
        GLint _alpha = 0;

        GLuint _diffuseMapUID = 0;
        GLuint _specularMapUID = 0;
        GLuint _shininessMapUID = 0;
        GLuint _alphaMapUID = 0;
        GLuint _normalMapUID = 0;

        GLuint _useDiffuseMapUID = 0;
        GLuint _useSpecularMapUID = 0;
        GLuint _useShininessMapUID = 0;
        GLuint _useAlphaMapUID = 0;
        GLuint _useNormalMapUID = 0;

        GLuint _isTextLabelUID = 0;

        GLint _numLights = 0; // uniform id
        size_t totalNumLights = 0; // actual counter

        glm::mat4 _viewM; // camera view matrix
        glm::mat4 _projectionM; // perspective projection matrix
        glm::vec3 _position;

    public:
        Shader();

        static glm::vec3 getWorldAmbient() { return WORLD_AMBIENT; }

        virtual void applyMaterialUniforms(std::shared_ptr<Material> mat);
        virtual void setLight(Light *light, int lightIndex);
        virtual void updateLight(Light* light);

        virtual GLuint init(std::string vertShaderLocation, std::string fragShaderLocation);
        virtual void update(Camera &camera, int winWidth, int winHeight);
        virtual void draw(Mesh &mesh, bool drawTransparent);
    };
}


#endif //PGR_SEM_COPAKOND_SHADER_H
