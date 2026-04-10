#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include "pgr.h"
#include "../geometry/material.h"
#include "../geometry/geometry.h"

namespace copakond {
    class Mesh : public Geometry {
    protected:
        GLuint _shaderProgram;
        GLuint _vboVertices;
        GLuint _vboNormals;
        GLuint _vao;
        GLsizei _numVertices;

        std::shared_ptr<Material> _material = std::make_shared<Material>();

    public:
        Mesh();
        Mesh(const glm::vec3 &translation);
        Mesh(const glm::vec3 &translation, const glm::vec3 &rotation);
        Mesh(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

        void setMaterial(const std::shared_ptr<Material> &material);
        std::shared_ptr<Material> getMaterial();

        virtual void init(GLuint shader);
        virtual void draw();
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H
