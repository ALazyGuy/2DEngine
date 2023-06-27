#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer/ShaderProgram.h"
#include "resources/ResourceManager.h"
#include "renderer/Texture2D.h"

int windowWidth = 800;
int windowHeight = 600;

GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat text[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

void onWindowResize(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void onKeyPressed(GLFWwindow* window, int key, int scanCode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char **argv) {
    if (!glfwInit()) {
        std::cout << "GLFW init failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", nullptr, nullptr);
    if (!window) {
        std::cout << "Error while creating window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, onWindowResize);
    glfwSetKeyCallback(window, onKeyPressed);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load glad" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

    {
        ResourceManager resourceManager(argv[0]);
        auto shaderProgram = resourceManager.loadShader("Default", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

        auto texture = resourceManager.loadTexture("Map", "res/textures/map_16x16.png");

        if (!shaderProgram) {
            std::cerr << "Can't create shader" << std::endl;
            return -1;
        }

        if (!shaderProgram->isCompiled()) {
            std::cerr << "Can't create shader" << std::endl;
            return -1;
        }

        GLuint pointsVbo = 0;
        glGenBuffers(1, &pointsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colorsVbo = 0;
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint textVbo = 0;
        glGenBuffers(1, &textVbo);
        glBindBuffer(GL_ARRAY_BUFFER, textVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(text), text, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, textVbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        shaderProgram->use();
        shaderProgram->setTexture("tex", 0);

        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(vao);
            texture->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}