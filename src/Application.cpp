#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>


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

    glfwTerminate();

    return 0;
}