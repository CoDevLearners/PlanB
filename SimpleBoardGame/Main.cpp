#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>
#include <iostream>

int main(int, char**)
{
	glfwInit();
	glfwSetTime(0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(800, 600, "Plan B", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		glfwTerminate();
		return -2;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
	glfwSwapBuffers(window);

	glfwSetCursorPosCallback(window, [](GLFWwindow*, double x, double y) {
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow*, int button, int action, int modifiers) {
	});

	glfwSetKeyCallback(window, [](GLFWwindow*, int key, int scancode, int action, int mods) {
	});

	glfwSetCharCallback(window, [](GLFWwindow*, unsigned int codepoint) {
	});

	glfwSetDropCallback(window, [](GLFWwindow*, int count, const char** filenames) {
	});

	glfwSetScrollCallback(window, [](GLFWwindow*, double x, double y) {
	});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
	});

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
