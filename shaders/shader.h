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
        GLuint _shaderProgram;

        GLuint _worldAmbientUID;

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

        GLuint _diffuseMapUID;
        GLuint _specularMapUID;
        GLuint _shininessMapUID;
        GLuint _alphaMapUID;
        GLuint _normalMapUID;

        GLuint _useDiffuseMapUID;
        GLuint _useSpecularMapUID;
        GLuint _useShininessMapUID;
        GLuint _useAlphaMapUID;
        GLuint _useNormalMapUID;

        GLint _numLights; // uniform id
        size_t totalNumLights; // actual counter

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
