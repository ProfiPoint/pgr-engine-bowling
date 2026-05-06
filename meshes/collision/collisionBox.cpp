#include "collisionBox.h"

namespace copakond {
    CollisionBox::CollisionBox(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool debug) :
    Mesh(position, rotation, scale), _debug(debug) {
        if (debug) {
            _material = std::make_shared<Material>();
            _material->ambient() = glm::vec3(0.19f, 0.36f, 0.86f);
            _material->diffuse() = glm::vec3(0.19f, 0.36f, 0.86);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        } else {
            _material = std::make_shared<Material>();
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.0f;
        }
    }

    void CollisionBox::init(GLuint shader) {
        _shaderProgram = shader;

        // Define the 36 vertices of a 1x1x1 cube centered at origin
        std::vector<float> vertices = {
            // back
            1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           -1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2, -1.0f/2,

           // front
            1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,

           -1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,

           // left
           -1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,

           -1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           // right
            1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,

            1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,

           // bottom
            1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           -1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2,  1.0f/2,

           // top
            1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,

           -1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2
       };

        _numVertices = vertices.size() / 3;

        //BINDING VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        // VERTICES
        glGenBuffers(1, &_vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        GLint position = glGetAttribLocation(_shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // NORMALS (used vertices as normals, because light doesnt matter here)
        glGenBuffers(1, &_vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        GLint normal = glGetAttribLocation(_shaderProgram, "normal");
        glEnableVertexAttribArray(normal);
        glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void CollisionBox::draw(float deltaTime) {
        if (!_debug) { return; }
        Mesh::draw(deltaTime);
    }


    bool CollisionBox::collisionCheck(Mesh mesh) {
        return false; // TODO: collision checks
    }

}