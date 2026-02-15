//Practica#2     Murillo Rodriguez Sarah Sofia
//15/02/2026     422130448
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 800;



int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers vértices usados para el punto, la línea, cuadrado y el primer triángulo
	float vertices[] = {
		//0.5f,  0.5f, 0.0f,    1.0f,1.0f,0.0f,  // top right posición | color arriba izquierda
		//0.5f, 0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right arriba derecha
		//-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left abajo izquierda
		//-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 

		//Cara Mickey
			// Triángulo 1
		0.03f,  0.03f, 0.00f,  0.0f, 0.0f, 0.0f, //A
		-0.03f, 0.03f, 0.00f,    0.0f, 0.0f, 0.0f, //B
		-0.03f, -0.03f, 0.0f,   0.0f, 0.0f, 0.0f, //C

			 // Triángulo 2
		0.03f,  0.03f, 0.0f,   0.0f, 0.0f, 0.0f,
		0.08f, -0.03f, 0.0f,     0.0f, 0.0f, 0.0f, //NUEVO D
		-0.03f, -0.03f, 0.0f,     0.0f, 0.0f, 0.0f,

		// Triángulo 3
		-0.09f,  -0.04f, 0.0f,   0.0f, 0.0f, 0.0f,//NUEVO E
		-0.03f, 0.03f, 0.0f,     0.0f, 0.0f, 0.0f,
		-0.03f, -0.03f, 0.0f,     0.0f, 0.0f, 0.0f,

		// Triángulo 4
		-0.09f,  -0.04f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.03f, -0.15f, 0.0f,     0.0f, 0.0f, 0.0f, // NUEVO F
		-0.03f, -0.03f, 0.0f,     0.0f, 0.0f, 0.0f,

		// Triángulo 5
		-0.03f, -0.03f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.03f, -0.09f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO G
		0.08f, -0.03f, 0.0f,    0.0f, 0.0f, 0.0f,

		// Triángulo 6
		0.08f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,  // NUEVO H
		-0.03f, -0.09f, 0.0f,   0.0f, 0.0f, 0.0f,
		0.08f, -0.03f, 0.0f,    0.0f, 0.0f, 0.0f,

		// Triángulo 7
		-0.03f, -0.15f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.03f, -0.09f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.03f, -0.11f, 0.0f,     0.0f, 0.0f, 0.0f,//NUEVO I

		// Triángulo 8
		-0.03f, -0.15f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.01f, -0.15f, 0.0f,     0.0f, 0.0f, 0.0f, //NUEVO J
		0.03f, -0.11f, 0.0f,     0.0f, 0.0f, 0.0f,

		// Triángulo 9
		0.08f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,  // NUEVO H
		0.03f, -0.11f, 0.0f,    0.0f, 0.0f, 0.0f, //NUEVO I
		0.01f, -0.15f, 0.0f,    0.0f, 0.0f, 0.0f, //NUEVO J

		// Triángulo 10
		-0.09f,  -0.04f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.09f, -0.08f, 0.0f,    0.0f, 0.0f, 0.0f, //NUEVO K
		-0.05f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f, //NUEVO L

		// Triángulo 11
		-0.08f,  -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,//NUEVO M
		-0.09f, -0.08f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.05f, -0.12f, 0.0f,     0.0f, 0.0f, 0.0f,

		// Triángulo 12
		-0.03f, -0.15f, 0.0f,     0.0f, 0.0f, 0.0f, // NUEVO F
		-0.05f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,//NUEVO L
		-0.08f,  -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,//NUEVO M

		//Oreja Izq
			// Triángulo 13
		-0.09f,  -0.04f, 0.0f,   0.0f, 0.0f, 0.0f, //E
		-0.03f, 0.03f, 0.00f,    0.0f, 0.0f, 0.0f, //B
		-0.09f, 0.08f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO N

		// Triángulo 14
		-0.03f,  0.05f, 0.0f,   0.0f, 0.0f, 0.0f, // NUEVO P
		-0.03f, 0.03f, 0.00f,   0.0f, 0.0f, 0.0f, //B
		-0.06f, 0.06f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO O

		// Triángulo 15
		-0.03f,  0.05f, 0.0f,   0.0f, 0.0f, 0.0f, // NUEVO P
		-0.06f, 0.08f, 0.00f,   0.0f, 0.0f, 0.0f, // Q
		-0.06f, 0.06f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO O

		// Triángulo 15
		-0.09f, 0.08f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO N
		-0.06f, 0.08f, 0.00f,   0.0f, 0.0f, 0.0f, // Q
		-0.06f, 0.06f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO O

		// Triángulo 16
		-0.09f, 0.08f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO N
		-0.15f, 0.01f, 0.00f,    0.0f, 0.0f, 0.0f, // NUEVO S
		-0.09f, -0.04f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO R

		// Triángulo 17
		-0.12f, -0.04f, 0.0f,    0.0f, 0.0f, 0.0f, // NUEVO T
		-0.15f, 0.01f, 0.00f,    0.0f, 0.0f, 0.0f,// NUEVO S
		-0.09f, -0.04f, 0.0f,   0.0f, 0.0f, 0.0f,// NUEVO R

		//Oreja Der
		//Triangulo 18
		0.03f,  0.03f, 0.00f,   0.0f, 0.0f, 0.0f, //A
		0.08f, -0.03f, 0.0f,    0.0f, 0.0f, 0.0f, // D
		0.10f, 0.01f, 0.0f,     0.0f, 0.0f, 0.0f, // NUEVO U

		//Triangulo 19
		0.03f, 0.03f, 0.00f, 0.0f, 0.0f, 0.0f, //A
		0.10f, 0.01f, 0.0f,  0.0f, 0.0f, 0.0f, //  U
		0.03f, 0.07f, 0.00f, 0.0f, 0.0f, 0.0f, //NUEVO V

		//Triangulo 20
		0.10f, 0.01f, 0.0f,  0.0f, 0.0f, 0.0f, //  U
		0.03f, 0.07f, 0.00f, 0.0f, 0.0f, 0.0f, // V
		0.09f, 0.08f, 0.00f, 0.0f, 0.0f, 0.0f, //NUEVO W

		//Triangulo 21
		0.10f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  U
		0.09f, 0.08f, 0.00f, 0.0f, 0.0f, 0.0f, // W
		0.12f, 0.07f, 0.00f, 0.0f, 0.0f, 0.0f, // NUEVO X

		//Triangulo 22
		0.10f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  U
		0.12f, 0.07f, 0.00f, 0.0f, 0.0f, 0.0f, // X
		0.13f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  Y

		//Triangulo 23
		0.08f, -0.03f, 0.0f, 0.0f, 0.0f, 0.0f, // D
		0.10f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  U
		0.13f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  Y

		//Triangulo 23
		0.08f, -0.03f, 0.0f, 0.0f, 0.0f, 0.0f, // D
		0.13f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f, //  Y
		0.12f, -0.02f, 0.0f, 0.0f, 0.0f, 0.0f, // Z
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	}; //uso de vertices para triangulo con vértices en diferente orden



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //solo poner el contorno

       // glPointSize(20); //punto argumento es el grosor del punto
        //glDrawArrays(GL_POINTS,0,1); //dibujar un punto argumento desde donde inicio y cuántos elementos del arreglo voy a dibujar
        
        //glDrawArrays(GL_LINES,0,4); //linea
        //glDrawArrays(GL_LINE_LOOP,0,4); //cuadrado
        
        glDrawArrays(GL_TRIANGLES,0,75); //tringulo vertices definidos
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0); //tringulo orden distinto

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}