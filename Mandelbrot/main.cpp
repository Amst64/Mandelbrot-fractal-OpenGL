#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <vector>

int window_width = 1280;

int window_height = 720;

static void key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)

{
}

static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/)

{
}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/)

{
}

static void cursor_position_callback(GLFWwindow* /*window*/, double /*xpos*/, double /*ypos*/)

{
}

static void size_callback(GLFWwindow* /*window*/, int width, int height)

{
    window_width = width;

    window_height = height;
}

struct Vertex2DColor

{
    glm::vec2 position;

    glm::vec3 color;

    Vertex2DColor();

    Vertex2DColor(glm::vec2 _position, glm::vec3 _color)
        : position{_position}, color{_color}

    {
    }
};

int main(int argc, char* argv[])
{
    int a = argc;
    a++;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Mandelbrot", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    glimac::FilePath applicationPath(argv[0]);
    glimac::Program program = loadProgram(applicationPath.dirPath() + "Mandelbrot/shaders/mandelbrot.vs.glsl", applicationPath.dirPath() + "Mandelbrot/shaders/mandelbrot.fs.glsl");
    program.use();

    //quad
    std::vector<glm::vec2> vertices;

    vertices.push_back(glm::vec2(-1.0f, 1.0f));
    vertices.push_back(glm::vec2(1.0f, 1.0f));
    vertices.push_back(glm::vec2(-1.0f, -1.0f));
    vertices.push_back(glm::vec2(1.0f, -1.0f));
    //

    //Création d'un VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Binding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Envoie des données
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    //Debind le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //tableau des indices des sommets
    std::vector<uint32_t> indices;

    //les indices des sommets
    //premier triangle
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    //deuxieme triangle
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);

    //Création d'un IBO
    GLuint ibo;
    glGenBuffers(1, &ibo);

    //Binding du IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //Envoie des données dans ibo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    //Debind le IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Création d'un VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Binding du VAO
    glBindVertexArray(vao);

    //Binding du IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //Activation des attributs vertex
    const GLuint VERTEX_ATTR_POSITION = 0;
    //const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    //glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    //Spécification des attributs de vertex
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const GLvoid*)0);
    //glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, color));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Debind le VAO
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();

    return 0;
}