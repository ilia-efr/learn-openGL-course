#ifndef LEARNOGL_COURSE_SHADER_H
#define LEARNOGL_COURSE_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertPath, const char* fragPath);
    void Delete();
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name,  glm::mat4 &value) const;
};


#endif //LEARNOGL_COURSE_SHADER_H
