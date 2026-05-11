#ifndef PGR_SEM_COPAKOND_LEVELEDITOR_H
#define PGR_SEM_COPAKOND_LEVELEDITOR_H

#include <map>

#include "../scene.h"

namespace copakond {
    /** @brief Transformation modes for the runtime level editor */
    enum class EditMode { NONE, TRANSLATE, ROTATE, SCALE };

    /** @brief Axis lock for current transformation */
    enum class EditAxe { NONE, X, Y, Z };

    /** @brief Stores a snapshot of object's transform for saving or undo operations */
    struct StateSaved { glm::vec3 position; glm::vec3 rotation; glm::vec3 scale; };

    /** @brief Runtime editor utility allowing the user to pick, move, and save mesh transformations */
    class LevelEditor {
    private:
        Scene* _scene;
        Mesh* _selectedMesh = nullptr;
        EditMode _currentMode = EditMode::NONE;
        EditAxe _currentAxe = EditAxe::NONE;

        std::map<Mesh*, StateSaved> _modifiedMeshes;

        static std::string floatToString(float value);
        static std::string vec3ToString(const glm::vec3& v);

    public:
        LevelEditor(Scene* scene) : _scene(scene) {}

        /** @brief Selects an object based on stencil buffer ID */
        void onObjectClickedEvent(int id);

        /** @brief Handles transformation switching and applying delta modifications */
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown);
        void onMouseWheelEvent(int wheel, int direction, int x, int y);

        /** @brief Exports modified mesh transformations to a text file */
        void saveSnapshot(std::string filename = "meshes.txt");
        void undo();

        EditMode getEditMode() const { return _currentMode; }
        EditAxe getEditAxe() const { return _currentAxe; }
    };
}

#endif //PGR_SEM_COPAKOND_LEVELEDITOR_H
