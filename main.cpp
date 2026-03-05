#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // -- initialization and window creation --
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr,
                                          nullptr);
    if (window == nullptr){
       std::cout << "Failed to load glfw window" << std::endl;
       glfwTerminate();
       return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // -- SHADERS --
    Shader shaderProgram("vertex_shader.vs",
                         "frag_shader.fs");

    // -- bg color definition --
    float r = 0.2f;
    float g = 0.3f;
    float b = 0.3f;
    float a = 1.0f;

    // -- vertex defintion --
    float vertices[] = {
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };


    // --VBO VAO EBO defintion and setup --
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // triangle setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float )));
    glEnableVertexAttribArray(1);

    // -- debug for wireframe mode --
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // -- render loop --
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);


        // --triangle draw--
        shaderProgram.use();

//        float timeVal = glfwGetTime();
//        float greenVal = static_cast<float>(sin(timeVal) / 2.0f + 0.5f);
//        shaderProgram.setFloat("", 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shaderProgram.Delete();
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
