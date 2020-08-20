#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>

// READ ALL THE DOCS RELATED TO THESE FUNCS.
static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);


    // Error handling.
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    // If false it means the shader did NOT compile successfully.
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));           // This is dynamically creating on the STACK, noramally dynamic creation happens on the HEAP, save worrying about forgetting to DELETE it later on.

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : " frag") << '\n';
        std::cout << message << '\n';

        glDeleteShader(id);
        return 0;
    }

    return id;
}

// READ ALL THE DOCS RELATED TO THESE FUNCS.
static unsigned int createShader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// READ ALL THE DOCS RELATED TO THESE FUNCS.
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        std::cout << "glew init failed!\n";
    }

    // Print out the version of GL we are using.
    //std::cout << glGetString(GL_VERSION) << '\n';

    // Vertex position for drawing a triangle. 2D.
    float positions[6] = { -0.5f, -0.5f,
                            0.0f, 0.5f,
                            0.5f, -0.5f };
    unsigned int buffer;
    glGenBuffers(1, &buffer);                                                       // Create a buffer.
    glBindBuffer(GL_ARRAY_BUFFER, buffer);                                          // Bind (Select/Change state to) the buffer we just created, remember OpenGL is just a state machine.
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);    // Copy the vertex positions in to the buffer.

    // Actually enable the array.
    glEnableVertexAttribArray(0);

    // Define how many and the type of positions we have 1D, 2D, 3D, 4D, ints, floats etc.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int shader = createShader(vertexShader, fragShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing things the old way 'Immediate Mode'
        /*glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.0f, 0.5f);
            glVertex2f(0.5f, -0.5f);
        glEnd();*/

        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}