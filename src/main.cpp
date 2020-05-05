#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Unable to initialize glfw!\n");
        return -1;
    }

    auto window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (!window) {
        fprintf(stderr, "Unable to create glfw window!\n");
        glfwTerminate();
        return -2;
    }

    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGL()) {
        fprintf(stderr, "Unable to load OpenGL!\n");
        glfwTerminate();
        return -3;
    }
    fprintf(stderr, "Using OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.027f, 0.149f, 0.149f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
