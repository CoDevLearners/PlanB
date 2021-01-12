// Include
//////////////////////////////////////////////////////////////////////////
// Std
#include <algorithm>
// Third
#include <OpenGLWrapper.h>
namespace gw = glwrapper;
#include <glfw/glfw3.h>
#include <nanogui/nanogui.h>
#include <nanogui/nanogui.h>
#include <BuffaloChessGameLib.h>
// Local
#include "shaders.h"
//////////////////////////////////////////////////////////////////////////


// Structures
//////////////////////////////////////////////////////////////////////////
struct UserData
{
	gw::Camera* camera;
};


// Functions
//////////////////////////////////////////////////////////////////////////
GLFWwindow* CreateOpenGLWindow();
void SetCursorPosCallback(GLFWwindow*, double x, double y);
void SetMouseButtonCallback(GLFWwindow*, int button, int action, int modifiers);
void SetScrollCallback(GLFWwindow*, double x, double y);
void SetFramebufferSizeCallback(GLFWwindow*, int width, int height);


// Main
//////////////////////////////////////////////////////////////////////////
int main()
{
	// Game Resrouece
	//////////////////////////////////////////////////////////////////////////
	GLFWwindow* window = CreateOpenGLWindow();
	IBuffaloChess* game = IBuffaloChess::CreateGame();
	gw::Camera* camera = new gw::Camera();
	gw::Shader* shader = new gw::Shader(base_vert, base_frag);
	gw::Texture* texture = new gw::Texture("BoardPattern.png");
	gw::Sampler* nearSampler = gw::Sampler::Builder()
		.Filter_Min(GL_NEAREST)
		.Filter_Mag(GL_NEAREST)
		.Wrap_S(GL_REPEAT)
		.Wrap_T(GL_REPEAT)
		.Build_Ptr();
	gw::Plane* board = new gw::Plane(11.f, 7.f);

	UserData userData;
	userData.camera = camera;


	// Initialize Value
	//////////////////////////////////////////////////////////////////////////
	camera->setViewport(0, 0, 800, 400);
	camera->setPos(glm::vec3(0, 0, 5));
	camera->lookAt(glm::vec3(0, 0, 0));
	nearSampler->Bind(0);


	// Window Event
	//////////////////////////////////////////////////////////////////////////
	glfwSetCursorPosCallback(window, SetCursorPosCallback);
	glfwSetMouseButtonCallback(window, SetMouseButtonCallback);
	glfwSetScrollCallback(window, SetScrollCallback);
	glfwSetFramebufferSizeCallback(window, SetFramebufferSizeCallback);
	glfwSetWindowUserPointer(window, (void*)&userData);


	// Game Loop
	//////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		glViewport(0, 0, camera->getWidth(), camera->getHeight());
		glClearColor(1.f, 0.25f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		texture->Bind(GL_TEXTURE0);

		auto mvpMat = camera->getProjectionMatrix() * camera->getViewMatrix();
		shader->Set_mat4("u_mvpMat", glm::value_ptr(mvpMat));
		shader->Set_vec2("u_tiling", glm::value_ptr(glm::vec2(5.5f, 3.5f)));

		{
			gw::AutoVertexArray vao;
			board->Bind();
			board->Draw();
		}

		glfwSwapBuffers(window);
	}

	return 0;
}

GLFWwindow* CreateOpenGLWindow()
{
	glfwInit();
	glfwSetTime(0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

	GLFWwindow* window = glfwCreateWindow(800, 400, "Buffalo Chess", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		(void)glGetError();
		return nullptr;
	}

	return window;
}

void SetCursorPosCallback(GLFWwindow* window, double x, double y)
{
	auto userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));
	auto camera = userData->camera;

	static glm::vec2 prevPos(-1, -1);

	if (prevPos.x < 0)
	{
		prevPos = glm::vec2((float)x, (float)y);
		return;
	}


	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::vec2 pos((float)x, (float)y);
	float dx = (pos.x - prevPos.x) / width;
	float dy = (prevPos.y - pos.y) / height;

	// 왼쪽 클릭 상태
	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		camera->rotateAround(dx * glm::pi<float>(), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
		camera->rotateAround(dy * glm::pi<float>(), glm::vec3(0, 0, 0), camera->getRight());
	}

	// 오른쪽 클릭 상태
	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		camera->translate(camera->getFront() * (dx + dy));
	}

	prevPos = pos;
}

void SetMouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
{
}

void SetScrollCallback(GLFWwindow* w, double x, double y)
{
}

void SetFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	auto userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));
	auto camera = userData->camera;

	height = height == 0 ? 1 : height;

	camera->setViewport(0, 0, width, height);
	camera->setPerspMode();
}
