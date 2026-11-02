#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

namespace {

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

struct Engine {
    GLFWwindow* window = nullptr;
    GLuint shaderProgram = 0;
    bool glfwInitialized = false;

    Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    ~Engine() {
        // Release OpenGL resources while the window's context still exists.
        if (window) glfwMakeContextCurrent(window);
        if (shaderProgram) glDeleteProgram(shaderProgram);
        if (window) glfwDestroyWindow(window);
        if (glfwInitialized) glfwTerminate();
    }

    static GLuint compileShader(GLenum type, const char* source) {
        const GLuint shader = glCreateShader(type);
        if (!shader) {
            std::cerr << "Failed to create shader\n";
            return 0;
        }

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[1024] = {};
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Shader compilation failed: " << infoLog << '\n';
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    bool setupShaders() {
        const char* vertexSource = R"(#version 330 core
        layout (location = 0) in vec2 aPos;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
        }
        )";
        const char* fragmentSource = R"(#version 330 core
        out vec4 FragColor;
        uniform vec4 uColor;
        void main() {
            FragColor = uColor;
        }
        )";

        const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
        if (!vertexShader) return false;

        const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
        if (!fragmentShader) {
            glDeleteShader(vertexShader);
            return false;
        }

        shaderProgram = glCreateProgram();
        if (!shaderProgram) {
            std::cerr << "Failed to create shader program\n";
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return false;
        }
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GLint success = GL_FALSE;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[1024] = {};
            glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Shader program linking failed: " << infoLog << '\n';
            return false;
        }
        return true;
    }

    int run() {
        glfwSetErrorCallback([](int code, const char* description) {
            std::cerr << "GLFW error " << code << ": " << description << '\n';
        });
        if (!glfwInit()) return EXIT_FAILURE;
        glfwInitialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(800, 600, "Algorithm", nullptr, nullptr);
        if (!window) return EXIT_FAILURE;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cerr << "Failed to initialize GLAD\n";
            return EXIT_FAILURE;
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        if (!setupShaders()) return EXIT_FAILURE;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Drawing logic can be added here later.

            glfwSwapBuffers(window);
        }
        return EXIT_SUCCESS;
    }
};

} // namespace

int main() {
    Engine engine;
    return engine.run();
}
