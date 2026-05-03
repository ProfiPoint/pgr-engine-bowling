#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include <memory>

#include "../pgr-portable.h"
#include "../geometry/material.h"
#include "../geometry/geometry.h"

namespace copakond {
    struct SubMesh {
        std::shared_ptr<Material> material;
        unsigned int indexOffset;
        unsigned int indexCount;
    };

    class Mesh : public Geometry {
    private:

        std::vector<float> _vertices = std::vector<float>();

    protected:
        static int globalMeshCounter;
        int id;

        GLuint _shaderProgram;
        GLuint _vboVertices;
        GLuint _vboNormals;
        GLuint _vao;
        GLsizei _numVertices;

        std::shared_ptr<Material> _material = std::make_shared<Material>();
        std::vector<SubMesh> _subMeshes;

        void _SetId();

    public:
        Mesh();
        Mesh(const glm::vec3 &translation);
        Mesh(const glm::vec3 &translation, const glm::vec3 &rotation);
        Mesh(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

        void setVertices(const std::vector<float> &vertices);
        void setMaterial(const std::shared_ptr<Material> &material);
        const std::vector<SubMesh>& getSubMeshes() const { return _subMeshes; }
        std::shared_ptr<Material> getMaterial();

        GLuint getVao() const { return _vao; }
        GLsizei getNumVertices() const { return _numVertices; }

        virtual void init(GLuint shader);
        virtual void draw();
        int getId() const { return id; }
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H
