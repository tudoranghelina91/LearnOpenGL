#include <iostream>
#include <GLAD\glad.h>
#include <GLFW\glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// Set the frame buffer size callback for a particular window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set up vertex data: We need to use a Vertex Buffer Object which contains vertex data in 3D coordinates from -1 to 1. Anything outside this range will not be rendered on screen
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// We need a vertex array object VAO - When we want to draw something else, we just need to swap the VAO?
	// Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs.
	// If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;

	// generate a buffer id and output the generated it through a variable (i.e. VBO above)
	glGenBuffers(1, &VBO);

	// bind to the array buffer the vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// buffer the data to the bound buffer (VBO). Mode specifies how the GPU manages the data.
		//GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		//GL_STATIC_DRAW : the data is set only once and used many times.
		//GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Write the shader. This will draw the triangle
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// CREATE VERTEX SHADER
	// Create shader and return a shader id
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Set the shader source for the shader
	// 1 represents the number of strings used for source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compile the shader
	glCompileShader(vertexShader);

	// Get vertex shader compilation status
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// get shader information for shaderId, length of info log and the object that will output
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// CREATE FRAGMENT SHADER
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor; \n\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// CREATE THE SHADER PROGRAM USING THE VERTEX AND FRAGMENT SHADERS
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach shaders and link them to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	glUseProgram(shaderProgram);

	// After the program was built (compiled) we don't need the shaders anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VBO contains our vertex data.
	// It can contain positions but also other types of data.
	// That's why we need to configure the vertex attribute pointer to know how to iterate through the array.

	// 0 comes from the vertex shader (layout location = 0)
	// 3 comes from the vertex shader - vec3
	// GL_FLOAT represents the data type from the vec3 values (vec3 is made up of floats)
	// Normalize the data? i.e map whatever values are there from -1 to 1 = GL_FALSE
	// The size in bytes of the float data type. We basically jump the memory locations (stride)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	// The render loop - one iteration = 1 frame
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering starts here
		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// rendering ends here
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}