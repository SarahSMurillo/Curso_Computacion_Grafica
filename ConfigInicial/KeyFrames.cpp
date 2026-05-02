//Practica 12        Murillo Rodriguez Sarah Sofia
//01-05-2026       422130448
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();
void SaveAnimation(const std::string& filename);
void LoadAnimation(const std::string& filename);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f, 2.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f)
};

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 Light1 = glm::vec3(0);

float rotBall = 0.0f;
float rotDog = 0.0f;
int dogAnim = 0;
float FLegs = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;
float F_LeftLegRot = 0.0f;
float F_RightLegRot = 0.0f;
float B_LeftLegRot = 0.0f;
float B_RightLegRot = 0.0f;
float bodyRotx = 0.0f;
float bodyRotz = 0.0f;
float bodyRoty_lean = 0.0f;
float dogPosY_offset = 0.0f;
float headPitch = 0.0f;
float dogPosX, dogPosY, dogPosZ;

#define MAX_FRAMES 2000
int i_max_steps = 190;
int i_curr_steps = 0;

typedef struct _frame {
    float rotDog, rotDogInc;
    float dogPosX, dogPosY, dogPosZ;
    float incX, incY, incZ;
    float head, headInc;
    float tail, tailInc;
    float F_LeftLegRot, F_LeftLegRotInc;
    float F_RightLegRot, F_RightLegRotInc;
    float B_LeftLegRot, B_LeftLegRotInc;
    float B_RightLegRot, B_RightLegRotInc;
    float bodyRotx, bodyRotXInc;
    float bodyRotz, bodyRotZInc;
    float bodyRoty_lean, bodyRoty_leanInc;
    float dogPosY_offset, dogPosY_offsetInc;
    float headPitch, headPitchInc;
} FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;

// =====================================================================
//  GUARDAR animacion en AnimacionesKeyFrames/nombre.txt
//  Llama a esta funcion con el nombre que quieras
// =====================================================================
void SaveAnimation(const std::string& filename)
{
    system("if not exist AnimacionesKeyFrames mkdir AnimacionesKeyFrames");
    std::string path = "AnimacionesKeyFrames\\" + filename + ".txt";
    std::ofstream file(path);
    if (!file.is_open()) { std::cout << "[ANIM] Error al crear " << path << "\n"; return; }

    file << "frames " << FrameIndex << "\n";
    file << "steps " << i_max_steps << "\n";
    for (int i = 0; i < FrameIndex; i++) {
        file << "\n[keyframe " << i << "]\n";
        file << "dogPosX " << KeyFrame[i].dogPosX << "\n";
        file << "dogPosY " << KeyFrame[i].dogPosY << "\n";
        file << "dogPosZ " << KeyFrame[i].dogPosZ << "\n";
        file << "rotDog " << KeyFrame[i].rotDog << "\n";
        file << "head " << KeyFrame[i].head << "\n";
        file << "headPitch " << KeyFrame[i].headPitch << "\n";
        file << "tail " << KeyFrame[i].tail << "\n";
        file << "F_LeftLegRot " << KeyFrame[i].F_LeftLegRot << "\n";
        file << "F_RightLegRot " << KeyFrame[i].F_RightLegRot << "\n";
        file << "B_LeftLegRot " << KeyFrame[i].B_LeftLegRot << "\n";
        file << "B_RightLegRot " << KeyFrame[i].B_RightLegRot << "\n";
        file << "bodyRotx " << KeyFrame[i].bodyRotx << "\n";
        file << "bodyRotz " << KeyFrame[i].bodyRotz << "\n";
        file << "bodyRoty_lean " << KeyFrame[i].bodyRoty_lean << "\n";
        file << "dogPosY_offset " << KeyFrame[i].dogPosY_offset << "\n";
    }
    file.close();
    char abs[512];
    _fullpath(abs, path.c_str(), sizeof(abs));
    std::cout << "[ANIM] Guardado: " << abs << " (" << FrameIndex << " keyframes)\n";
}

// =====================================================================
//  CARGAR animacion desde AnimacionesKeyFrames/nombre.txt
// =====================================================================
void LoadAnimation(const std::string& filename)
{
    std::string path = "AnimacionesKeyFrames\\" + filename + ".txt";
    std::ifstream file(path);
    if (!file.is_open()) { std::cout << "[ANIM] No se encontro: " << path << "\n"; return; }

    FrameIndex = 0;
    for (int i = 0; i < MAX_FRAMES; i++) KeyFrame[i] = {};

    std::string token;
    int cf = -1;
    while (file >> token) {
        if (token == "frames") { file >> FrameIndex; if (FrameIndex > MAX_FRAMES) FrameIndex = MAX_FRAMES; }
        else if (token == "steps") { file >> i_max_steps; }
        else if (token == "[keyframe") { file >> cf; std::string cl; file >> cl; }
        else if (cf >= 0 && cf < MAX_FRAMES) {
            float v; file >> v;
            if (token == "dogPosX")        KeyFrame[cf].dogPosX = v;
            else if (token == "dogPosY")        KeyFrame[cf].dogPosY = v;
            else if (token == "dogPosZ")        KeyFrame[cf].dogPosZ = v;
            else if (token == "rotDog")         KeyFrame[cf].rotDog = v;
            else if (token == "head")           KeyFrame[cf].head = v;
            else if (token == "headPitch")      KeyFrame[cf].headPitch = v;
            else if (token == "tail")           KeyFrame[cf].tail = v;
            else if (token == "F_LeftLegRot")   KeyFrame[cf].F_LeftLegRot = v;
            else if (token == "F_RightLegRot")  KeyFrame[cf].F_RightLegRot = v;
            else if (token == "B_LeftLegRot")   KeyFrame[cf].B_LeftLegRot = v;
            else if (token == "B_RightLegRot")  KeyFrame[cf].B_RightLegRot = v;
            else if (token == "bodyRotx")       KeyFrame[cf].bodyRotx = v;
            else if (token == "bodyRotz")       KeyFrame[cf].bodyRotz = v;
            else if (token == "bodyRoty_lean") KeyFrame[cf].bodyRoty_lean = v;
            else if (token == "dogPosY_offset") KeyFrame[cf].dogPosY_offset = v;
        }
    }
    file.close();

    if (FrameIndex > 0) {
        dogPosX = KeyFrame[0].dogPosX; dogPosY = KeyFrame[0].dogPosY; dogPosZ = KeyFrame[0].dogPosZ;
        rotDog = KeyFrame[0].rotDog; head = KeyFrame[0].head; headPitch = KeyFrame[0].headPitch;
        tail = KeyFrame[0].tail; F_LeftLegRot = KeyFrame[0].F_LeftLegRot;
        F_RightLegRot = KeyFrame[0].F_RightLegRot; B_LeftLegRot = KeyFrame[0].B_LeftLegRot;
        B_RightLegRot = KeyFrame[0].B_RightLegRot; bodyRotx = KeyFrame[0].bodyRotx;
        dogPosY_offset = KeyFrame[0].dogPosY_offset;
    }
    play = false; playIndex = 0; i_curr_steps = 0;
    std::cout << "[ANIM] Cargada: " << filename << " (" << FrameIndex << " keyframes). Presiona L para reproducir.\n";
}

void saveFrame(void)
{
    printf("frameindex %d\n", FrameIndex);
    KeyFrame[FrameIndex].dogPosX = dogPosX; KeyFrame[FrameIndex].dogPosY = dogPosY;
    KeyFrame[FrameIndex].dogPosZ = dogPosZ; KeyFrame[FrameIndex].rotDog = rotDog;
    KeyFrame[FrameIndex].head = head;    KeyFrame[FrameIndex].tail = tail;
    KeyFrame[FrameIndex].F_LeftLegRot = F_LeftLegRot;  KeyFrame[FrameIndex].F_RightLegRot = F_RightLegRot;
    KeyFrame[FrameIndex].B_LeftLegRot = B_LeftLegRot;  KeyFrame[FrameIndex].B_RightLegRot = B_RightLegRot;
    KeyFrame[FrameIndex].bodyRotx = bodyRotx;
    KeyFrame[FrameIndex].bodyRotz = bodyRotz;
    KeyFrame[FrameIndex].bodyRoty_lean = bodyRoty_lean;       KeyFrame[FrameIndex].dogPosY_offset = dogPosY_offset;
    KeyFrame[FrameIndex].headPitch = headPitch;
    FrameIndex++;
}

void resetElements(void)
{
    dogPosX = KeyFrame[0].dogPosX; dogPosY = KeyFrame[0].dogPosY; dogPosZ = KeyFrame[0].dogPosZ;
    head = KeyFrame[0].head;    tail = KeyFrame[0].tail;     rotDog = KeyFrame[0].rotDog;
    F_LeftLegRot = KeyFrame[0].F_LeftLegRot;  F_RightLegRot = KeyFrame[0].F_RightLegRot;
    B_LeftLegRot = KeyFrame[0].B_LeftLegRot;  B_RightLegRot = KeyFrame[0].B_RightLegRot;
    bodyRotx = KeyFrame[0].bodyRotx;
    bodyRotz = KeyFrame[0].bodyRotz;
    bodyRoty_lean = KeyFrame[0].bodyRoty_lean;       dogPosY_offset = KeyFrame[0].dogPosY_offset;
    headPitch = KeyFrame[0].headPitch;
}

void interpolation(void)
{
    KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
    KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
    KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;
    KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;
    KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;
    KeyFrame[playIndex].F_LeftLegRotInc = (KeyFrame[playIndex + 1].F_LeftLegRot - KeyFrame[playIndex].F_LeftLegRot) / i_max_steps;
    KeyFrame[playIndex].F_RightLegRotInc = (KeyFrame[playIndex + 1].F_RightLegRot - KeyFrame[playIndex].F_RightLegRot) / i_max_steps;
    KeyFrame[playIndex].B_LeftLegRotInc = (KeyFrame[playIndex + 1].B_LeftLegRot - KeyFrame[playIndex].B_LeftLegRot) / i_max_steps;
    KeyFrame[playIndex].B_RightLegRotInc = (KeyFrame[playIndex + 1].B_RightLegRot - KeyFrame[playIndex].B_RightLegRot) / i_max_steps;
    KeyFrame[playIndex].bodyRotXInc = (KeyFrame[playIndex + 1].bodyRotx - KeyFrame[playIndex].bodyRotx) / i_max_steps;
    KeyFrame[playIndex].bodyRotZInc = (KeyFrame[playIndex + 1].bodyRotz - KeyFrame[playIndex].bodyRotz) / i_max_steps;
    KeyFrame[playIndex].bodyRoty_leanInc = (KeyFrame[playIndex + 1].bodyRoty_lean - KeyFrame[playIndex].bodyRoty_lean) / i_max_steps;
    KeyFrame[playIndex].dogPosY_offsetInc = (KeyFrame[playIndex + 1].dogPosY_offset - KeyFrame[playIndex].dogPosY_offset) / i_max_steps;
    KeyFrame[playIndex].headPitchInc = (KeyFrame[playIndex + 1].headPitch - KeyFrame[playIndex].headPitch) / i_max_steps;
    KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;
}

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion KeyFrames Sarah Murillo", nullptr, nullptr);
    if (!window) { std::cout << "Failed to create GLFW window\n"; glfwTerminate(); return EXIT_FAILURE; }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) { std::cout << "Failed to initialize GLEW\n"; return EXIT_FAILURE; }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    Model DogBody((char*)"Models/DogBody.obj");
    Model HeadDog((char*)"Models/HeadDog.obj");
    Model DogTail((char*)"Models/TailDog.obj");
    Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
    Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
    Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
    Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");
    Model Piso((char*)"Models/piso.obj");
    Model Ball((char*)"Models/ball.obj");

    for (int i = 0; i < MAX_FRAMES; i++) KeyFrame[i] = {};

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // =====================================================================
    // Para guardar:  presiona P -> escribe nombre en consola -> Enter
    // Para cargar:   presiona O -> escribe nombre en consola -> Enter
    // Para limpiar y empezar nueva animacion: presiona C
    // =====================================================================
    std::cout << "\n=== Animacion KeyFrames ===\n";
    std::cout << "  K -> Guardar keyframe\n";
    std::cout << "  L -> Reproducir\n";
    std::cout << "  P -> Guardar animacion (escribe nombre en consola)\n";
    std::cout << "  O -> Cargar animacion  (escribe nombre en consola)\n";
    std::cout << "  C -> Limpiar keyframes para nueva animacion\n";
    std::cout << "===========================\n\n";

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();
        Animation();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glm::mat4 modelTemp = glm::mat4(1.0f);
        lightingShader.Use();
        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);

        glm::vec3 lightColor;
        lightColor.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor.z = sin(glfwGetTime() * Light1.z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

        glm::mat4 view = camera.GetViewMatrix();
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model(1);

        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(lightingShader);

        model = glm::mat4(1);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

        modelTemp = model = glm::translate(model, glm::vec3(dogPosX, dogPosY + dogPosY_offset, dogPosZ));
        modelTemp = model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTemp = model = glm::rotate(model, glm::radians(bodyRotx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::rotate(model, glm::radians(bodyRoty_lean), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTemp = model = glm::rotate(model, glm::radians(bodyRotz), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        DogBody.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
        model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(headPitch), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        HeadDog.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
        model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        DogTail.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
        model = glm::rotate(model, glm::radians(F_LeftLegRot), glm::vec3(-1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        F_LeftLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
        model = glm::rotate(model, glm::radians(F_RightLegRot), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        F_RightLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(0.082f, -0.046f, -0.218f));
        model = glm::rotate(model, glm::radians(B_LeftLegRot), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B_LeftLeg.Draw(lightingShader);

        model = modelTemp;
        model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
        model = glm::rotate(model, glm::radians(B_RightLegRot), glm::vec3(-1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B_RightLeg.Draw(lightingShader);

        model = glm::mat4(1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
        model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Ball.Draw(lightingShader);
        glDisable(GL_BLEND);
        glBindVertexArray(0);

        lampShader.Use();
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4(1);
        model = glm::translate(model, pointLightPositions[0]);
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_4]) head += 0.01f;
    if (keys[GLFW_KEY_5]) head -= 0.01f;
    if (keys[GLFW_KEY_6]) tail += 0.01f;
    if (keys[GLFW_KEY_7]) tail -= 0.01f;
    if (keys[GLFW_KEY_8]) F_LeftLegRot -= 0.01f;
    if (keys[GLFW_KEY_9]) F_LeftLegRot += 0.01f;
    if (keys[GLFW_KEY_1]) F_RightLegRot += 0.01f;
    if (keys[GLFW_KEY_0]) F_RightLegRot -= 0.01f;
    if (keys[GLFW_KEY_N]) B_LeftLegRot += 0.01f;
    if (keys[GLFW_KEY_M]) B_LeftLegRot -= 0.01f;
    if (keys[GLFW_KEY_E]) B_RightLegRot += 0.01f;
    if (keys[GLFW_KEY_F]) B_RightLegRot -= 0.01f;
    if (keys[GLFW_KEY_B]) bodyRotx += 0.01f;
    if (keys[GLFW_KEY_V]) bodyRotx -= 0.01f;
    if (keys[GLFW_KEY_COMMA])  bodyRotz += 0.5f;
    if (keys[GLFW_KEY_PERIOD]) bodyRotz -= 0.5f;
    if (keys[GLFW_KEY_LEFT_BRACKET])  bodyRoty_lean -= 0.5f;
    if (keys[GLFW_KEY_RIGHT_BRACKET]) bodyRoty_lean += 0.5f;
    if (keys[GLFW_KEY_Q]) dogPosY_offset += 0.001f;
    if (keys[GLFW_KEY_R]) dogPosY_offset -= 0.001f;
    if (keys[GLFW_KEY_X]) headPitch += 0.01f;
    if (keys[GLFW_KEY_Z]) headPitch -= 0.01f;
    if (keys[GLFW_KEY_2]) rotDog += 0.01f;
    if (keys[GLFW_KEY_3]) rotDog -= 0.01f;
    if (keys[GLFW_KEY_H]) dogPosZ += 0.01f;
    if (keys[GLFW_KEY_Y]) dogPosZ -= 0.01f;
    if (keys[GLFW_KEY_G]) dogPosX -= 0.01f;
    if (keys[GLFW_KEY_J]) dogPosX += 0.01f;

    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])    camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])  camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])  camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.ProcessKeyboard(RIGHT, deltaTime);
    if (keys[GLFW_KEY_T]) pointLightPositions[0].x += 0.01f;
    if (keys[GLFW_KEY_U]) pointLightPositions[0].z -= 0.01f;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)   keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }

    if (keys[GLFW_KEY_L]) {
        if (!play && FrameIndex > 1) {
            resetElements(); interpolation();
            play = true; playIndex = 0; i_curr_steps = 0;
        }
        else {
            play = false;
        }
    }

    if (keys[GLFW_KEY_K]) {
        if (FrameIndex < MAX_FRAMES) saveFrame();
    }

    // C -> limpiar keyframes para nueva animacion
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        FrameIndex = 0; play = false; playIndex = 0; i_curr_steps = 0;
        std::cout << "[ANIM] Keyframes limpiados. Graba una nueva animacion con K.\n";
    }

    // P -> guardar (la ventana se pausa, escribe en consola y Enter)
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        if (FrameIndex < 2) {
            std::cout << "[ANIM] Necesitas al menos 2 keyframes.\n";
        }
        else {
            std::string name;
            std::cout << "[ANIM] Nombre para guardar: ";
            std::cin >> name;
            SaveAnimation(name);
            FrameIndex = 0; play = false; playIndex = 0; i_curr_steps = 0;
            std::cout << "[ANIM] Listo. Graba una nueva animacion con K, o carga una con O.\n";
        }
    }

    // O -> cargar (la ventana se pausa, escribe en consola y Enter)
    if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        std::string name;
        std::cout << "[ANIM] Nombre de la animacion a cargar: ";
        std::cin >> name;
        LoadAnimation(name);
    }

    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (keys[GLFW_KEY_SPACE]) {
        active = !active;
        Light1 = active ? glm::vec3(0.2f, 0.8f, 1.0f) : glm::vec3(0);
    }
}

void Animation()
{
    if (play) {
        if (i_curr_steps >= i_max_steps) {
            playIndex++;
            if (playIndex > FrameIndex - 2) {
                printf("termina anim\n");
                playIndex = 0; play = false;
            }
            else {
                i_curr_steps = 0; interpolation();
            }
        }
        else {
            dogPosX += KeyFrame[playIndex].incX;
            dogPosY += KeyFrame[playIndex].incY;
            dogPosZ += KeyFrame[playIndex].incZ;
            head += KeyFrame[playIndex].headInc;
            tail += KeyFrame[playIndex].tailInc;
            F_LeftLegRot += KeyFrame[playIndex].F_LeftLegRotInc;
            F_RightLegRot += KeyFrame[playIndex].F_RightLegRotInc;
            B_LeftLegRot += KeyFrame[playIndex].B_LeftLegRotInc;
            B_RightLegRot += KeyFrame[playIndex].B_RightLegRotInc;
            bodyRotx += KeyFrame[playIndex].bodyRotXInc;
            bodyRotz += KeyFrame[playIndex].bodyRotZInc;
            bodyRoty_lean += KeyFrame[playIndex].bodyRoty_leanInc;
            dogPosY_offset += KeyFrame[playIndex].dogPosY_offsetInc;
            headPitch += KeyFrame[playIndex].headPitchInc;
            rotDog += KeyFrame[playIndex].rotDogInc;
            i_curr_steps++;
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse) { lastX = xPos; lastY = yPos; firstMouse = false; }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;
    lastX = xPos; lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}