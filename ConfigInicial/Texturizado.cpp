//Practica 7               Murillo  Rodriguez Sarah Sofia
//21-03-2026               422130448

#include <iostream>
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

// Other includes
#include "Shader.h"
#include "Camera.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

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
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texturizado Sarah Murillo", nullptr, nullptr);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Shader
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    GLfloat vertices[] =
    {
        //posición color textura
            -0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.932329f,0.279780f,  // 0
             0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.644327f,0.512665f,  // 1
             0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.644362f,0.281291f,  // 2
             0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.642588f,0.743618f,  // 3
            -0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.352396f,0.976797f,  // 4
             0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.354659f,0.744291f,  // 5
            -0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.641264f,0.047639f,  // 6
            -0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.355791f,0.280172f,  // 7
            -0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.353528f,0.045737f,  // 8
             0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.354265f,0.280307f,  // 9
            -0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.063825f,0.511459f,  // 10
            -0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.063508f,0.281084f,  // 11
             0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.642588f,0.513506f,  // 12
             0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.354659f,0.742035f,  // 13
             0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.353258f,0.512221f,  // 14
            -0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.643405f,0.281661f,  // 15
             0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.353459f,0.511468f,  // 16
            -0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.354659f,0.281444f,  // 17
            -0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.935132f,0.509944f,  // 18
            -0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.643230f,0.976097f,  // 19
            -0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.642099f,0.281451f,  // 20
             0.5f,-0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.353258f,0.511795f,  // 21
             0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,  0.642970f,0.743459f,  // 22
             0.5f, 0.5f,-0.5f,  1.0f,1.0f,1.0f,  0.642676f,0.511853f   // 23
    };

    GLuint indices[] =
    {
            0,1,2,
            3,4,5,
            6,7,8,
            9,10,11,
            12,13,14,
            15,16,17,
            0,18,1,
            3,19,4,
            6,20,7,
            9,21,10,
            12,22,13,
            15,23,16
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture Coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    //  Alineacion de 1 byte para texturas no cuadradas
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int textureWidth, textureHeight, nrChannels;
    unsigned char* image = stbi_load("images/Dado1.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    if (image)
    {
        // Imprime dimensiones para verificar
        std::cout << "Textura: " << textureWidth << "x" << textureHeight
            << " canales: " << nrChannels << std::endl;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight,
            0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);

    // Vincula el sampler una vez aqui
    lampShader.Use();
    glUniform1i(glGetUniformLocation(lampShader.Program, "ourTexture"), 0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lampShader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.GetZoom(),
            (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model(1);

        GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");

        //Textura activa antes de dibujar
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

 

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
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