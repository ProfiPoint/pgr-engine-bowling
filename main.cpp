#include <iostream>
#include "pgr-portable.h"
#include "meshes/mesh.h"
#include "meshes/objMesh.h"
#include "geometry/camera.h"
#include "light/light.h"
#include "utils/input.h"
#include "shaders/shader.h"
#include <algorithm>

namespace copakond {
    const char *WIN_TITLE = "PGR Semestral Work Copakond";
    int winWidth = 1280;
    int winHeight = 720;

    // shared variables
    uint64_t time = 0;
    std::vector<Mesh *> meshes = {};
    std::vector<Light *> lights = {};
    Shader shader = Shader();
    Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        100.0f
    );
    Input input = Input(camera, winWidth, winHeight);

    float updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
    }

    void init() {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        glEnable(GL_BLEND); // enable transparent colors
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        GLuint shaderPrg = shader.init(
            "shaders/shaders/shader.vert",
            "shaders/shaders/shader.frag"
        );

        std::shared_ptr<Material> teddyMaterial = std::make_shared<Material>(
            glm::vec3(0.5f, 0.33f, 0.2f) * 0.1f,
            glm::vec3(0.5f, 0.33f, 0.2f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            16.0f, 0.5f
        );

        glm::vec3 lightPosition = glm::vec3(-8.0f, 0.0f, 5.0f);
        glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 lightAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

        //Light *light = new SpotLight(lightPosition, lightDirection, lightAmbient, lightDiffuse, lightSpecular, 20.0f, 30.0f, 5.0f, false);
        //lights.push_back(light);
        Light *light1 = new PointLight(lightPosition, lightAmbient, lightDiffuse, lightSpecular, 10.0f, true);
        lights.push_back(light1);
        //Light *light2 = new DirectionalLight(-lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //lights.push_back(light2);

        //Light *light3 = new DirectionalLight(lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //lights.push_back(light3);

        //Mesh* triangleMesh = new Mesh();
        //meshes.push_back(triangleMesh);
        //Mesh *teddyMesh = new ObjMesh("meshes/models/teddy.obj", true);
        //teddyMesh->setMaterial(teddyMaterial);
        //meshes.push_back(teddyMesh);

        Mesh *oldShipMesh = new ObjMesh("meshes/models/ship.obj", true, glm::vec3(-10.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, -glm::pi<float>()/2, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f));
        oldShipMesh->setMaterial(teddyMaterial);
        meshes.push_back(oldShipMesh);

        Mesh *shipMesh = new ObjMesh("meshes/models/ship2.obj", false, glm::vec3(-5.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, glm::pi<float>(), 0.0f), glm::vec3(0.125f, 0.125f, 0.125f));
        meshes.push_back(shipMesh);

        Mesh *bodyMesh = new ObjMesh("meshes/models/characters/character-a.obj", false, glm::vec3(0.0f, -1.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        meshes.push_back(bodyMesh);

        Mesh *body2Mesh = new ObjMesh("meshes/models/characters/character-f.obj", false, glm::vec3(2.0f, -1.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        meshes.push_back(body2Mesh);

        for (Mesh *mesh: meshes) {
            mesh->init(shaderPrg);
        }
        for (size_t i = 0; i < lights.size(); i++) {
            shader.setLight(lights[i], i);
        }







        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCullFace( GL_BACK);
        glEnable(GL_CULL_FACE);

    }

    void draw() {
        float deltaTime = updateTime(); // calculate delta time
        input.keyInput(deltaTime); // process input

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.update(camera, winWidth, winHeight);

        // sort all meshes, from the furthest to the nearest (for transparent meshes), all meshes, could be optimized more...
        glm::vec3 camPos = camera.getPosition();
        std::sort(meshes.begin(), meshes.end(), [&camPos](Mesh* a, Mesh* b) {
                glm::vec3 pos1 = glm::vec3(a->getModelMatrix()[3]); // translation
                glm::vec3 pos2 = glm::vec3(b->getModelMatrix()[3]); // translation

                return glm::distance(camPos, pos1) > glm::distance(camPos, pos2);
        });

        for (Mesh *mesh: meshes) {
            //mesh->rotation().x += deltaTime * 1.0f;
            shader.draw(*mesh);
        }

        lights[0]->position() = camera.getPosition();
        shader.updateLight(lights[0]);

        glutSwapBuffers(); // swap front and back screen buffer
        glutPostRedisplay(); // !!!!!!!!! schedules display, doesnt stack!!!
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        input.keyboardInputEvent(key, x, y);
    }

    void specKeyboardInputEvent(int key, int x, int y) {
        input.specKeyboardInputEvent(key, x, y);
    }

    void keyboardUpInputEvent(unsigned char key, int x, int y) {
        input.keyboardUpInputEvent(key, x, y);
    }

    void specKeyboardUpInputEvent(int key, int x, int y) {
        input.specKeyboardUpInputEvent(key, x, y);
    }

    void mouseMoveEvent(int x, int y) {
        input.mouseMoveEvent(x, y);
    }

    void screenResizeEvent(int width, int height) {
        if (width == 0) width = 1; // sadly it can be 0 for some reason.
        if (height == 0) height = 1;

        winWidth = width;
        winHeight = height;

        glViewport(0, 0, width, height);
        input.update(winWidth, winHeight);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::winWidth, copakond::winHeight);
    glutCreateWindow(copakond::WIN_TITLE);

    // INPUT - keyboard and mouse event callbacks
    glutKeyboardFunc(copakond::keyboardInputEvent);
    glutSpecialFunc(copakond::specKeyboardInputEvent);
    glutKeyboardUpFunc(copakond::keyboardUpInputEvent);
    glutSpecialUpFunc(copakond::specKeyboardUpInputEvent);

    glutPassiveMotionFunc(copakond::mouseMoveEvent);
    glutSetCursor(GLUT_CURSOR_NONE); // hide cursor

    // SET DRAW CALLBACK
    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    copakond::init();

    glutMainLoop();
    return 0;
}
