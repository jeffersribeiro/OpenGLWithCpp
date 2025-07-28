#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <mesh.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float triangle1[] = {
        -1.0f, -0.5f, 0.0f, // V0
        -0.5f, -0.5f, 0.0f, // V1
        -0.5f, 0.5f, 0.0f   // V2
    };

    float triangle2[] = {
        0.0f, -0.5f, 0.0f, // V0
        0.0f, -0.5f, 0.0f, // V1
        0.5f, 0.5f, 0.0f   // V2
    };

    Mesh greenTriangle(triangle1, "shaders/green_shader.frag");
    Mesh blueTriangle(triangle2, "shaders/blue_shader.frag");

    greenTriangle.load();
    blueTriangle.load();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        greenTriangle.draw();
        blueTriangle.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    greenTriangle.dispose();
    blueTriangle.dispose();

    glfwTerminate();
    return 0;
}