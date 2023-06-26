#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

const char* VERTEX_SHADER = 
"#version 460\n"
"layout(location = 0) in vec3 vPosition;"
"layout(location = 1) in vec3 vColor;"
"out vec3 color;"
"void main(){"
"   color = vColor;"
"   gl_Position = vec4(vPosition, 1.0);"
"}";

const char* FRAGMENT_SHADER =
"#version 460\n"
"in vec3 color;"
"out vec4 rColor;"
"void main(){"
"   rColor = vec4(color, 1.0);"
"}";

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

int main(void) {
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

    GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertId, 1, &VERTEX_SHADER, nullptr);
    glCompileShader(vertId);

    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragId, 1, &FRAGMENT_SHADER, nullptr);
    glCompileShader(fragId);

    GLuint shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertId);
    glAttachShader(shaderProgramId, fragId);
    glLinkProgram(shaderProgramId);

    glDeleteShader(vertId);
    glDeleteShader(fragId);

    GLuint pointsVbo = 0;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorsVbo = 0;
    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgramId);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}