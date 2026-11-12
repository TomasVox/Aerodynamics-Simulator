#include "utils/utils.h"

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

struct Engine {
    GLFWwindow* window;

    GLuint shaderProgram = NULL;
    std::vector<GLuint> shaders;

    Engine() {
        if (!glfwInit()) {
            std::cerr << "Fallo al inicializar GLFW" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "Aerodynamics Simulator", NULL, NULL);
        if (window == NULL) {
            std::cerr << "Fallo al crear la ventana de GLFW" << std::endl;
            glfwTerminate();
            return -1;
        }
        
        glfwMakeContextCurrent(window);
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Fallo al inicializar GLAD" << std::endl;
            return -1;
        }

        glfwTerminate();
        return 0;
    }

    GLuint setShader(GLenum type, GLsizei id, std::string shaderPath)
    {
        const char* shaderSourceString = loadShaderFrom(shaderPath).c_str();

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, id, &shaderSourceString, NULL);
        glCompileShader(shader);

        shaders.push_back(shader);

        int success;
        char err[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, err);
            throw std::runtime_error("Error ocurred while compiling shader...");
            std::cout << err << std::endl;
        }

        if (!shaderProgram)
            shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, shader);

        return shader;
    }
};
