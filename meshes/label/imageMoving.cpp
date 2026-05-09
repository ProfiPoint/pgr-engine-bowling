#include "imageMoving.h"

namespace copakond {
    ImageMoving::ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated) {
        _movingSpeed = movingSpeed;
        _imageRepeated = imageRepeated;
        _material = std::make_shared<Material>();
        _material->ambient() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->diffuse() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
        _material->setDiffuseTexture(imagePath, true, false);
    }

    ImageMoving::ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated, std::shared_ptr<Material> material) {
        _movingSpeed = movingSpeed;
        _imageRepeated = imageRepeated;
        _material = material;
        _material->setDiffuseTexture(imagePath, true, false);
    }

    ImageMoving::~ImageMoving() {
        glDeleteBuffers(1, &_vboUvs);
    }

    void ImageMoving::_generateGeometry() {
        _uvs.clear();

        // set the correct corners
        float uLeft = _curOffset.x;
        float vDown = _curOffset.y;
        float uRight = uLeft + _imageRepeated.x;
        float vUp = vDown + _imageRepeated.y;

        _uvs.insert(_uvs.end(), {uLeft, vDown}); // left-down triangle
        _uvs.insert(_uvs.end(), {uRight, vDown});
        _uvs.insert(_uvs.end(), {uLeft, vUp});
        _uvs.insert(_uvs.end(), {uLeft, vUp});   // right-up triangle
        _uvs.insert(_uvs.end(), {uRight, vDown});
        _uvs.insert(_uvs.end(), {uRight, vUp});

        glBindBuffer(GL_ARRAY_BUFFER, _vboUvs);
        glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ImageMoving::init(GLuint shader) {
        _shaderProgram = shader;

        _vertices = { // unit square, 2 triangles
            -1.0f/2, -1.0f/2, 0.0f,
             1.0f/2, -1.0f/2, 0.0f,
            -1.0f/2,  1.0f/2, 0.0f,

            -1.0f/2,  1.0f/2, 0.0f,
             1.0f/2, -1.0f/2, 0.0f,
             1.0f/2,  1.0f/2, 0.0f
        };

        _normals = { // default orientation (world coord)
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        _numVertices = 6;
        _generateGeometry(); // update uvs based of the current frame

        //BINDING VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vboVertices);
        glGenBuffers(1, &_vboNormals);
        glGenBuffers(1, &_vboUvs);

        // VERTICES
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
        GLint position = glGetAttribLocation(_shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // NORMALS
        glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
        glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), GL_STATIC_DRAW);
        GLint normal = glGetAttribLocation(_shaderProgram, "normal");
        glEnableVertexAttribArray(normal);
        glVertexAttribPointer(normal, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

        // UVS
        glBindBuffer(GL_ARRAY_BUFFER, _vboUvs);
        glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_DYNAMIC_DRAW);
        GLint textureCoord = glGetAttribLocation(_shaderProgram, "textureCoord");
        glEnableVertexAttribArray(textureCoord);
        glVertexAttribPointer(textureCoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ImageMoving::draw(float deltaTime) {
        if (_numVertices == 0) { return; }

        glm::vec2 prevOffset = _curOffset;

        if (!_paused) {
            _curOffset += _movingSpeed * deltaTime;
            _curOffset = glm::mod(_curOffset, glm::vec2(1.0f, 1.0f));
        }

        if (prevOffset != _curOffset) {
            _generateGeometry();
        }

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }


}