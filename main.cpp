#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char *vertexShaderSource ="#version 330 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "}\0";

const char *fragmentShaderSource1 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(0.0f, 0.0f, 1.0f, 1"
                                   ".0f);\n"
                                   "} ";

const char *fragmentShaderSource2 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.0f, 0.0f, "
                                    "1.0f);\n"
                                    "} ";


const char *vertColorPass = "#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(aPos, 1.0f);\n"
                            "}\0";

const char *fragColorPass = "#version 330 core\n"
                           "out vec4 FragColor;\n"
                           "uniform vec4 ourColor;\n"
                           "void main()\n"
                           "{\n"
                           "FragColor = ourColor;\n"
                           "}\n\0";

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
    // -- vertex --
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertColorPass, NULL);
    glCompileShader(vertexShader);

    // -- vertex compilation success check --
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED \n" <<
                  std::endl;
    }

    // -- fragment --
    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragColorPass, NULL);
    glCompileShader(fragmentShader1);


    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG1::COMPILATION FAILED \n" <<
                  std::endl;
    }


    // -- shader program
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();

    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    glGetShaderiv(shaderProgram1, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM1::LINK FAILED \n" <<
                  std::endl;
    }

    // -- shader cleanup --
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);

    // -- bg color definition --
    float r = 0.2f;
    float g = 0.3f;
    float b = 0.3f;
    float a = 1.0f;

    // -- vertex defintion --
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
    };


    // --VBO VAO EBO defintion and setup --
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // -- first triangle setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    // -- debug for wireframe mode --
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // -- render loop --
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);


        // --triangle draw--
        glUseProgram(shaderProgram1);

        float timeVal = glfwGetTime();
        float greenVal = static_cast<float>(sin(timeVal) / 2.0f + 0.5f);
        int vertexColorLocation = glGetUniformLocation(shaderProgram1,
                                                       "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram1);

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
