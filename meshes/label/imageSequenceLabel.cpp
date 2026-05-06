#include "imageSequenceLabel.h"

namespace copakond {
    ImageSequenceLabel::ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int
        imagesPerHeight) {

        _fps = fps;
        _totalFrames = totalFrames;
        _imagesPerWidth = imagesPerWidth;
        _imagesPerHeight = imagesPerHeight;

        _material = std::make_shared<Material>();
        _material->ambient() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->diffuse() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
        _material->setDiffuseTexture(imageSequencePath);
    }

    ImageSequenceLabel::ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int
        imagesPerHeight, std::shared_ptr<Material> material) {

        _fps = fps;
        _totalFrames = totalFrames;
        _imagesPerWidth = imagesPerWidth;
        _imagesPerHeight = imagesPerHeight;

        _material = material;
        _material->setDiffuseTexture(imageSequencePath);
    }

    ImageSequenceLabel::~ImageSequenceLabel() {
        glDeleteBuffers(1, &_vboUvs);
    }

    void ImageSequenceLabel::_generateGeometry() {
        _uvs.clear();

        // cur col and row of the given frame
        int col = _frame % _imagesPerWidth;
        int row = _frame / _imagesPerWidth;

        // uv coords of the given frame
        float uSize = 1.0f / (float)_imagesPerWidth;
        float vSize = 1.0f / (float)_imagesPerHeight;
        float uLeft = col * uSize;
        float uRight = uLeft + uSize;
        float vUp = 1.0f - (row * vSize);
        float vDown = vUp - vSize;

        // set uv maps
        _uvs.insert(_uvs.end(), {uLeft, vDown}); // left-down triangle
        _uvs.insert(_uvs.end(), {uRight, vDown});
        _uvs.insert(_uvs.end(), {uLeft, vUp});
        _uvs.insert(_uvs.end(), {uLeft, vUp}); // right-up triangle
        _uvs.insert(_uvs.end(), {uRight, vDown});
        _uvs.insert(_uvs.end(), {uRight, vUp});

        glBindBuffer(GL_ARRAY_BUFFER, _vboUvs);
        glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ImageSequenceLabel::init(GLuint shader) {
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

    void ImageSequenceLabel::draw(float deltaTime) {
        if (_numVertices == 0) { return; }

        int prevFrame = _frame;

        if (!_paused) {
            _frameTime += deltaTime;

            float timePerFrame = 1.0f / (float)_fps;
            int framesAdding = (int)(_frameTime / timePerFrame);

            _frame += framesAdding;
            _frame = _frame % _totalFrames;
            _frameTime = fmod(_frameTime, timePerFrame);
        }

        if (prevFrame != _frame) {
            _generateGeometry();
        }

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }


}