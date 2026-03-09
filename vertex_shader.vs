#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    //mat4 MVP = P * V * M ;
    gl_Position = P * V * M * vec4(aPos, 1.0); // apply model-view-projection transformation
    ourColor = aColor;
    TexCoord = aTexCoord;
}