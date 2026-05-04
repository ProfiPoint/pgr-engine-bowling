//
// Created by profipoint on 5/4/2026.
//

#include "textLabelMesh.h"

namespace copakond {
    std::string TextLabelMesh::_alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;!@#$%^&*+-=()[]{}<>'\"\\`~|";

    TextLabelMesh::TextLabelMesh(const std::string& fontImagePath) {
        _numCharacters = _alphabet.length();
        _material = std::make_shared<Material>();
        _material->ambient() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->diffuse() = glm::vec3(1.0f, 1.0f, 1.0f);
        _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
        _material->setDiffuseTexture(fontImagePath);
        _material->setIsTextLabel(true);
        _material->setAlpha(0.0f); // set the default ambient and diff to fully transparent
    }

    TextLabelMesh::TextLabelMesh(const std::string& fontImagePath, std::shared_ptr<Material> material) {
        _numCharacters = _alphabet.length();
        _material = material;
        _material->setDiffuseTexture(fontImagePath);
        _material->setIsTextLabel(true);
        _material->setAlpha(0.0f); // set the default ambient and diff to fully transparent
    }

    TextLabelMesh::~TextLabelMesh() {
        glDeleteBuffers(1, &_vboUvs);
    }

    void TextLabelMesh::setText(const std::string& text) {
        _text = text;
        _generateGeometry();
    }

    void TextLabelMesh::setColor(const glm::vec3 &color) const {
        _material->ambient() = color / 2.0f;
        _material->diffuse() = color;
    }

    // correctly map each character to make is streached for the enitre character
    void TextLabelMesh::_generateGeometry() {
        _vertices.clear();
        _normals.clear();
        _uvs.clear();

        int len = _text.length();
        if (len == 0) {
            _numVertices = 0;
            return;
        }

        float charWidth = 1.0f / len;
        float uvWidth = 1.0f / _numCharacters;

        for (int i = 0; i < len; ++i) {
            char currentCharacter = _text[i];

            // searching for the given character in the loop
            size_t foundIndex = 0; // if character not found, use space (space is always the first character in that img!)
            for (size_t j = 0; j < _alphabet.size(); ++j) {
                if (_alphabet[j] == currentCharacter) {
                    foundIndex = j;
                    break;
                }
            }

            // world coordinates
            float x_left = -0.5f + (i * charWidth);
            float x_right = x_left + charWidth;
            float y_bottom = -0.5f;
            float y_top = 0.5f;

            // UV coordinates
            float u_left = foundIndex * uvWidth;
            float u_right = u_left + uvWidth;
            float v_bottom = 0.0f;
            float v_top = 1.0f;

            // fill vertices, uvs and normals (instead of telling the shader idnexes of the characteres, remap the uv map instead)
            _vertices.insert(_vertices.end(), {x_left, y_bottom, 0.0f});
            _uvs.insert(_uvs.end(), {u_left, v_bottom});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f}); // world coordinates

            _vertices.insert(_vertices.end(), {x_right, y_bottom, 0.0f});
            _uvs.insert(_uvs.end(), {u_right, v_bottom});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f});

            _vertices.insert(_vertices.end(), {x_left, y_top, 0.0f});
            _uvs.insert(_uvs.end(), {u_left, v_top});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f});

            _vertices.insert(_vertices.end(), {x_left, y_top, 0.0f});
            _uvs.insert(_uvs.end(), {u_left, v_top});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f});

            _vertices.insert(_vertices.end(), {x_right, y_bottom, 0.0f});
            _uvs.insert(_uvs.end(), {u_right, v_bottom});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f});

            _vertices.insert(_vertices.end(), {x_right, y_top, 0.0f});
            _uvs.insert(_uvs.end(), {u_right, v_top});
            _normals.insert(_normals.end(), {0.0f, 0.0f, 1.0f});
        }

        _numVertices = _vertices.size() / 3;

        if (_vao != 0) {
            glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
            glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
            glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, _vboUvs);
            glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind
        }
    }

    void TextLabelMesh::init(GLuint shader) {
        _shaderProgram = shader;

        //BINDING VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vboVertices);
        glGenBuffers(1, &_vboNormals);
        glGenBuffers(1, &_vboUvs);
        // REMOVED: glGenBuffers(1, &_ebo);

        // VERTICES
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
        // CHANGED TO DYNAMIC DRAW
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_DYNAMIC_DRAW);

        GLint position = glGetAttribLocation(_shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // NORMALS
        glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
        glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), GL_DYNAMIC_DRAW);

        GLint normal = glGetAttribLocation(_shaderProgram, "normal");
        glEnableVertexAttribArray(normal);
        glVertexAttribPointer(normal, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

        // UVS
        if (!_uvs.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, _vboUvs);
            glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_DYNAMIC_DRAW);

            GLint textureCoord = glGetAttribLocation(_shaderProgram, "textureCoord");
            glEnableVertexAttribArray(textureCoord);
            glVertexAttribPointer(textureCoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        }

        // REMOVED ALL EBO LOGIC HERE

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void TextLabelMesh::draw(float deltaTime) {
        if (_numVertices == 0) { return; }

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }

} // copakond