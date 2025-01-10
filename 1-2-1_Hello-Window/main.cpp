#include <iostream>
#include <GLAD\glad.h>
#include <GLFW\glfw3.h>

// function to resize the viewport alongside with the window on resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// Close window when ESC pressed
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
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Instantiate a window object with 800 by 600 px resolution with title LearnOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set the window as the active window of opengl
	glfwMakeContextCurrent(window);

	// GLAD manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// We need a viewport before we render anything to the screen.
	// Instantiate a viewport that takes the entire window
	// starting from the lower left corner at (X, Y)
	glViewport(0, 0, 800, 600);

	// Set the frame buffer size callback for a particular window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// The render loop - one iteration = 1 frame
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering goes here

		// set background color to RGBA values
		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Poll all events
		// - e.g. check if window resized and call the handler
		// - e.g. check if window is closing and call the handler
		// - e.g. keyboard input etc.
		glfwPollEvents();

		// Swap the front buffer with the back buffer, there are two buffers (one shows on screen, other isn't)
		glfwSwapBuffers(window);
	}

	// Always call this method to do clean-up on glfw
	glfwTerminate();

	return 0;
}