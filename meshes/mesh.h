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
    protected:
        static int globalMeshCounter;
        int id;
        int _isVertexWave = false;
        bool _visible = true;

        GLuint _shaderProgram = 0;
        GLuint _vboVertices = 0;
        GLuint _vboNormals = 0;
        GLuint _vao = 0;

        GLsizei _numVertices = 0;

        std::vector<float> _vertices = std::vector<float>();
        std::shared_ptr<Material> _material = std::make_shared<Material>();
        std::vector<SubMesh> _subMeshes;

        void _SetId();

    public:
        Mesh();
        Mesh(const glm::vec3 &position);
        Mesh(const glm::vec3 &position, const glm::vec3 &rotation);
        Mesh(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
        virtual ~Mesh();

        void setVertices(const std::vector<float> &vertices);
        void setMaterial(const std::shared_ptr<Material> &material);
        const std::vector<SubMesh>& getSubMeshes() const { return _subMeshes; }
        std::shared_ptr<Material> getMaterial();

        GLuint getVao() const { return _vao; }
        GLsizei getNumVertices() const { return _numVertices; }

        virtual void init(GLuint shader);
        virtual void draw(float deltaTime);
        int getId() const { return id; }

        void setVertexWave(bool isVertexWave) { _isVertexWave = isVertexWave; }
        bool isVertexWave() const { return _isVertexWave; }

        void hide() { _visible = false; }
        void show() { _visible = true; }
        void setVisible(bool visible) { _visible = visible; }
        bool isVisible() const { return _visible; }
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H
