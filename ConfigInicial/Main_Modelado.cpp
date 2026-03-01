//Practica 4                  Murillo Rodriguez Sarah Sofia
//01 de marzo de 2026         422130448


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "objectColor"); //nuevo para el color

		view = glm::translate(view, glm::vec3(movX,movY, movZ)); //Se mueve con lo que hay en las variables
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		////Agregando MESA 
	 //   model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(3.0f, 0.1f, 2.0f)); // Nueva línea Ancho, grosor, profundidad
		//model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f)); //segunda nueva línea, subir mesa
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		////Hacer pata uno de la mesa
		//model = glm::mat4(1.0f); //iniciando otra matriz
		//model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.1f)); //tamaño de la pata
		//model = glm::translate(model, glm::vec3(2.9f, -0.6f, 1.9f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		////Hacer pata dos de la mesa
		//model = glm::mat4(1.0f); //iniciando otra matriz
		//model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.1f)); //tamaño de la pata
		//model = glm::translate(model, glm::vec3(-2.9f, -0.6f, 1.9f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		////Hacer pata tres de la mesa
		//model = glm::mat4(1.0f); //iniciando otra matriz
		//model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.1f)); //tamaño de la pata
		//model = glm::translate(model, glm::vec3(-2.9f, -0.6f, -1.9f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		////Hacer pata cuatro de la mesa
		//model = glm::mat4(1.0f); //iniciando otra matriz
		//model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.1f)); //tamaño de la pata
		//model = glm::translate(model, glm::vec3(2.9f, -0.6f, -1.9f)); 
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		////fin de la mesa cuatro


	
	
		// Matriz gallo (para la rotación)
		glm::mat4 base = glm::mat4(1.0f);
		base = glm::rotate(base, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Cabeza (cresta)
		model = base;
		model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.957f, 0.322f, 0.290f); //rojo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.4f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.957f, 0.322f, 0.290f); //rojo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.4f, 0.8f, -0.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.957f, 0.322f, 0.290f); //rojo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fin cresta

		//inicio cabeza
		model = base;
		model = glm::translate(model, glm::vec3(-1.5f, 0.4f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.996f, 0.776f, 0.122f); //amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ojos
		model = base;
		model = glm::translate(model, glm::vec3(-1.75f, 0.45f, 0.30f));
		model = glm::scale(model, glm::vec3(0.10f, 0.15f, 0.02f));
		glUniform3f(colorLoc, 0.067f, 0.224f, 0.349f); // negro azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.77f, 0.45f, 0.25f));
		model = glm::scale(model, glm::vec3(0.10f, 0.15f, 0.10f));
		glUniform3f(colorLoc, 0.067f, 0.224f, 0.349f); // negro azuk
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.75f, 0.45f, -0.30f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.10f, 0.15f, 0.02f));
		glUniform3f(colorLoc, 0.067f, 0.224f, 0.349f); // negro azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.77f, 0.45f, -0.25f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.10f, 0.15f, 0.10f));
		glUniform3f(colorLoc, 0.067f, 0.224f, 0.349f); // negro azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pico
		model = base;
		model = glm::translate(model, glm::vec3(-1.77f, 0.42f, 0.00f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.50f, 0.20f, 0.20f));
		glUniform3f(colorLoc, 0.957f, 0.553f, 0.180f); // naranja
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//cresta abajo
		model = base;
		model = glm::translate(model, glm::vec3(-1.80f, 0.13f, 0.00f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.20f, 0.40f, 0.20f));
		glUniform3f(colorLoc, 0.957f, 0.322f, 0.290f); //rojo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//fin cabeza

		//inicio cuerpo

		model = base;
		model = glm::translate(model, glm::vec3(-1.25f, -0.2f, 0.00f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.8f, 0.6f, 0.6f));
		glUniform3f(colorLoc, 0.996f, 0.776f, 0.122f); //amarillo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ala der
		model = base;
		model = glm::translate(model, glm::vec3(-1.15f, -0.15f, 0.3f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.2f));
		glUniform3f(colorLoc, 0.957f, 0.553f, 0.180f); // naranja
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ala izq
		model = base;
		model = glm::translate(model, glm::vec3(-1.15f, -0.15f, -0.3f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.2f));
		glUniform3f(colorLoc, 0.957f, 0.553f, 0.180f); // naranja
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fin cuerpo

		//inicio cola
		model = base;
		model = glm::translate(model, glm::vec3(-0.70f, 0.3f, 0.0f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniform3f(colorLoc, 0.843f, 0.384f, 0.675f); //morado
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = base;
		model = glm::translate(model, glm::vec3(-0.45f, 0.23f, 0.0f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.25f, 0.60f, 0.25f));
		glUniform3f(colorLoc, 0.373f, 0.353f, 0.624f); //azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-0.60f, -0.14f, 0.0f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.50f, 0.15f, 0.25f));
		glUniform3f(colorLoc, 0.086f, 0.361f, 0.486f); //azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//fin cola

		//inicio patas
		model = base;
		model = glm::translate(model, glm::vec3(-1.20f, -0.55f, 0.2f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.2f));
		glUniform3f(colorLoc, 0.996f, 0.776f, 0.122f); //amarillo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pierna
		model = base;
		model = glm::translate(model, glm::vec3(-1.30f, -0.75f, 0.2f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.20f, 0.30f, 0.2f));
		glUniform3f(colorLoc, 0.698f, 0.224f, 0.404f); //morado
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//pies derecho
		model = base;
		model = glm::translate(model, glm::vec3(-1.31f, -0.85f, 0.2f)); 
		model = glm::scale(model, glm::vec3(0.20f, 0.08f, 0.25f));
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f); // azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// dedo 1
		model = base;
		model = glm::translate(model, glm::vec3(-1.45f, -0.85f, 0.28f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.10f));
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// dedo 2
		model = base;
		model = glm::translate(model, glm::vec3(-1.45f, -0.85f, 0.12f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.10f));
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pie izquierdo

		//inicio patas
		model = base;
		model = glm::translate(model, glm::vec3(-1.20f, -0.55f, -0.2f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.2f));
		glUniform3f(colorLoc, 0.996f, 0.776f, 0.122f); //amarillo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pierna
		model = base;
		model = glm::translate(model, glm::vec3(-1.30f, -0.75f, -0.2f)); //horizontal z vertical x y arriba abajo
		model = glm::scale(model, glm::vec3(0.20f, 0.30f, 0.2f));
		glUniform3f(colorLoc, 0.698f, 0.224f, 0.404f); //morado
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = base;
		model = glm::translate(model, glm::vec3(-1.31f, -0.85f, -0.2f)); // bajar más
		model = glm::scale(model, glm::vec3(0.20f, 0.08f, 0.25f)); // plano en Y
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f); // azul
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// dedo 1
		model = base;
		model = glm::translate(model, glm::vec3(-1.45f, -0.85f, -0.28f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.10f));
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// dedo 2
		model = base;
		model = glm::translate(model, glm::vec3(-1.45f, -0.85f, -0.12f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.10f));
		glUniform3f(colorLoc, 0.063f, 0.608f, 0.796f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0); //poner al final de todo lo que se tiene que dibujar
				
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE salir
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //mover derecha
		 movX += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //mover izquierda
		 movX -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // alejar
		 movZ -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // acercar
		 movZ += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) //girar derecha
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) //girar izquierda
		 rot -= 0.4f;
 }


