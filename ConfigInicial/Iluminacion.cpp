// Practica 8        Murillo Rodriguez Sarah Sofia
// 29-03-2026        422130448

//Std. Includes
#include <string>

//GLEW
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

//GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Otras librerías
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//Posiciones del Sol 
glm::vec3 lightPosSun(0.0f, 5.0f, 0.0f);
//Angulo de posicion del Sol en la orbita
float angleSun = 0.0f;
//Tamaño de mi orbita
float radiusSun = 8.0f;
bool animateSun = false;

//Posiciones de la Luna
glm::vec3 lightPosMoon(0.0f, 5.0f, 0.0f);
//Angulo de posicion de la Luna en la orbita
float angleMoon = 180.0f;
//Tamaño de mi orbita
float radiusMoon = 8.0f;
bool animateMoon = false;

//Velocidad de mi rotacion
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

float rot = 0.0f;
bool activanim = false;


//Nuevas variables
//Interruptor de movimiento, cuando presione la tecla L u O
bool sunCycleActive = false;
bool moonCycleActive = false;
//Angulo de inicio y fin
float sunStartAngle = 0.0f;
float moonStartAngle = 180.0f;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Materiales e Iluminacion Sarah Murillo", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    //Shader
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    //Cargando modelos
    Model espacio((char*)"Models/Untitled.obj");
    Model luna((char*)"Models/half moon.obj");
    Model sol((char*)"Models/sun.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 500.0f);

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

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        // Actualizar angulos
        if (sunCycleActive)
        {
            angleSun += 30.0f * deltaTime;
            if (angleSun >= sunStartAngle + 360.0f)
            {
                angleSun = sunStartAngle; // regresa exacto al inicio
                sunCycleActive = false;   // se para solo
            }
        }

        if (moonCycleActive)
        {
            angleMoon += 25.0f * deltaTime;
            if (angleMoon >= moonStartAngle + 360.0f)
            {
                angleMoon = moonStartAngle;
                moonCycleActive = false;
            }
        }

        // Calcular posiciones orbitales
        lightPosSun.x = radiusSun * cos(glm::radians(angleSun));
        lightPosSun.y = radiusSun * sin(glm::radians(angleSun)); // sin restriccion de abs para orbita completa
        lightPosSun.z = 0.0f;

        lightPosMoon.x = radiusMoon * cos(glm::radians(angleMoon));
        lightPosMoon.y = radiusMoon * sin(glm::radians(angleMoon));
        lightPosMoon.z = 0.0f;

        // Color de fondo segun si es de dia o noche
        float sunHeight = glm::clamp(lightPosSun.y / radiusSun, 0.0f, 1.0f);
        float moonHeight = glm::clamp(lightPosMoon.y / radiusMoon, 0.0f, 1.0f);

        glm::vec3 skyColor = glm::mix(
            glm::vec3(0.0f, 0.0f, 0.05f),   // noche
            glm::vec3(0.4f, 0.6f, 1.0f),     // dia
            sunHeight
        );
        glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();

        // Calcular luz dominante
        glm::vec3 dominantLightPos;
        glm::vec3 ambientColor, diffuseColor;

        if (sunHeight >= moonHeight)
        {
            dominantLightPos = lightPosSun;
            ambientColor = glm::vec3(0.6f, 0.55f, 0.4f) * sunHeight;
            diffuseColor = glm::vec3(1.0f, 0.95f, 0.8f) * sunHeight;
        }
        else
        {
            dominantLightPos = lightPosMoon;
            ambientColor = glm::vec3(0.1f, 0.1f, 0.2f) * moonHeight;
            diffuseColor = glm::vec3(0.3f, 0.3f, 0.5f) * moonHeight;
        }

        //  ESCENARIO con lightingShader
        lightingShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
            camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"),
            dominantLightPos.x, dominantLightPos.y, dominantLightPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"),
            ambientColor.x, ambientColor.y, ambientColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"),
            diffuseColor.x, diffuseColor.y, diffuseColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.3f, 0.3f, 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        glm::mat4 modelEspacio(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelEspacio));
        espacio.Draw(lightingShader);

        // SOL con shader simple (emite luz, no la recibe) ─
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 modelSol(1);
        modelSol = glm::translate(modelSol, lightPosSun);
        modelSol = glm::scale(modelSol, glm::vec3(0.8f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSol));
        sol.Draw(shader);

        //  LUNA con shader simple ──
        glm::mat4 modelMoon(1);
        modelMoon = glm::translate(modelMoon, lightPosMoon);
        modelMoon = glm::scale(modelMoon, glm::vec3(0.6f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMoon));
        luna.Draw(shader);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (activanim)
        if (rot > -90.0f) rot -= 0.1f;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)   keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        if (!sunCycleActive)
        {
            sunStartAngle = angleSun;
            sunCycleActive = true;
        }
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        if (!moonCycleActive)
        {
            moonStartAngle = angleMoon;
            moonCycleActive = true;
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}