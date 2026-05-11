#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include <memory>

#include "../pgr-portable.h"
#include "../geometry/material.h"
#include "../geometry/geometry.h"

namespace copakond {
    /** @brief Represents a part of a mesh that uses a specific material */
    struct SubMesh {
        std::shared_ptr<Material> material;
        unsigned int indexOffset; /**< Starting point in the element buffer (EBO) */
        unsigned int indexCount; /**< Number of indices to draw for this submesh */
    };

    /** @brief Base drawable 3D object containing geometry and material data */
    class Mesh : public Geometry {
    protected:
        static int globalMeshCounter; /**< Used to generate unique IDs for stencil buffer picking */
        int id;
        int _isVertexWave = false; /**< Flag for procedural vertex animation in shader */
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

        /** @brief Applies a material to the entire mesh and all its submeshes */
        void setMaterial(const std::shared_ptr<Material> &material);
        const std::vector<SubMesh>& getSubMeshes() const { return _subMeshes; }
        std::shared_ptr<Material> getMaterial();

        GLuint getVao() const { return _vao; }
        GLsizei getNumVertices() const { return _numVertices; }

        /**
         * @brief Initializes OpenGL buffers (VAO, VBO) for the mesh.
         * @param shader The compiled shader program ID used to get attribute locations.
         */
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
