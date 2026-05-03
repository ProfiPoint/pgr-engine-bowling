#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H

#include "../pgr-portable.h"
#include "../meshes/mesh.h"
#include "../geometry/camera.h"

namespace copakond {

class Skybox : public Mesh {
private:
    GLuint _shaderProgram = 0;
    GLuint _skyboxTextureUID = 0;

    GLuint _viewUID = 0;
    GLuint _projectionUID = 0;

public:
    Skybox();
    void draw() override;
    void update(Camera &camera, int winWidth, int winHeight);
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
