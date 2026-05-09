#include "levelEditor.h"

namespace copakond {
    void LevelEditor::onObjectClickedEvent(int id) {
        if (id <= 1) { // skybox selected
            _currentMode = EditMode::NONE;
            saveSnapshot();
            return;
        }

        // find the selected mesh
        std::vector<Mesh *> meshes = _scene->getMeshes();
        for (size_t i = 0; i < meshes.size(); i++) {
            Mesh *meshNow = meshes[i];
            if (id == meshNow->getId()) {
                _selectedMesh = meshNow;
                return;
            }
        }
    }

    void LevelEditor::onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {
        if (!isDown) { return; }

        const auto keysMap = _scene->getInput()->keysMap;


        // VECTOR MODE
        if (keysMap['r']) {
            keysMap['r'] = false;
            _currentMode = EditMode::ROTATE;
            std::cout << "ROTATE Mode selected" << std::endl;
        }
        else if (keysMap['t']) {
            keysMap['t'] = false;
            _currentMode = EditMode::TRANSLATE;
            std::cout << "TRANSLATE Mode selected" << std::endl;
        }
        else if (keysMap['z'] || keysMap['y']) {
            keysMap['z'] = false;
            keysMap['y'] = false;
            _currentMode = EditMode::SCALE;
            std::cout << "SCALE Mode selected" << std::endl;
        }

        // AXE
        else if (keysMap['1']) {
            keysMap['1'] = false;
            _currentAxe = EditAxe::X;
            std::cout << "X axe" << std::endl;
        }
        else if (keysMap['2']) {
            keysMap['2'] = false;
            _currentAxe = EditAxe::Y;
            std::cout << "Y axe" << std::endl;
        }
        else if (keysMap['3']) {
            keysMap['3'] = false;
            _currentAxe = EditAxe::Z;
            std::cout << "Z axe" << std::endl;
        }

        // STENCIL MODE
        else if (keysMap['8']) {
            keysMap['8'] = false;
            stencilMode = StencilSelect::ALL;
            std::cout << "StencilSelect::ALL" << std::endl;
        }
        else if (keysMap['9']) {
            keysMap['9'] = false;
            stencilMode = StencilSelect::MESHES;
            std::cout << "StencilSelect::MESHES" << std::endl;
        }
        else if (keysMap['0']) {
            keysMap['0'] = false;
            stencilMode = StencilSelect::COLLISION;
            std::cout << "StencilSelect::COLLISION" << std::endl;
        }

        else if (keysMap[KEY_BACKSPACE]) {
            _selectedMesh = nullptr;
            _currentMode = EditMode::NONE;
            std::cout << "unselected" << std::endl;
            saveSnapshot();
        }
    }

    void LevelEditor::onMouseWheelEvent(int wheel, int direction, int x, int y) {
        if (!_selectedMesh) { return;; }

        const auto keysMap = _scene->getInput()->keysMap;

        bool isShiftOn = false;
        bool isSuperShiftOn = false;
        bool isSelectAllAxesOn = false;
        float dir = 1.0f;

        if (keysMap[GLUT_KEY_SHIFT_L + IS_SPECIAL_KEY]) { isShiftOn = true; }
        if (keysMap[GLUT_KEY_ALT_L + IS_SPECIAL_KEY]) { isSuperShiftOn = true; }
        if (keysMap[GLUT_KEY_CTRL_L + IS_SPECIAL_KEY]) { isSelectAllAxesOn = true; }
        if (direction > 0) { dir = -dir; }


        switch (_currentMode) {
            case EditMode::TRANSLATE: {
                float value = 0.5f * dir;
                if (isShiftOn) { value = 0.05f * dir; }
                if (isSuperShiftOn) { value = 0.01f * dir; }

                if (isSelectAllAxesOn) {
                    _selectedMesh->position() += value * glm::vec3(1.0f);
                    break;
                }

                switch (_currentAxe) {
                    case EditAxe::X: _selectedMesh->position().x += value; break;
                    case EditAxe::Y: _selectedMesh->position().y += value; break;
                    case EditAxe::Z: _selectedMesh->position().z += value; break;
                }
                break;
            }

            case EditMode::ROTATE: {
                float value = glm::pi<float>() / 4.0f * dir;
                if (isShiftOn) { value = glm::pi<float>() / 12.0f * dir; }
                if (isSuperShiftOn) { value = glm::pi<float>() / 30.0f * dir; }

                if (isSelectAllAxesOn) {
                    _selectedMesh->rotation() += value * glm::vec3(1.0f);
                    break;
                }

                switch (_currentAxe) {
                    case EditAxe::X: _selectedMesh->rotation().x += value; break;
                    case EditAxe::Y: _selectedMesh->rotation().y += value; break;
                    case EditAxe::Z: _selectedMesh->rotation().z += value; break;
                }
                break;
            }

            case EditMode::SCALE: {
                float value = 0.5f * dir;
                if (isShiftOn) { value = 0.05f * dir; }
                if (isSuperShiftOn) { value = 0.01f * dir; }

                if (isSelectAllAxesOn) {
                    _selectedMesh->scale() += value * glm::vec3(1.0f);
                    break;
                }

                switch (_currentAxe) {
                    case EditAxe::X: _selectedMesh->scale().x += value; break;
                    case EditAxe::Y: _selectedMesh->scale().y += value; break;
                    case EditAxe::Z: _selectedMesh->scale().z += value; break;
                }
                break;
            }
        }
    }
    void LevelEditor::saveSnapshot(std::string filename) {}
}