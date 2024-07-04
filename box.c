#include <stdlib.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"

// shader source code
const char *vertexSource =
    "#version 150 core\n"
    "in vec3 aPos;\n"
    "in vec3 aNormal;\n"
    "in vec2 aTexCoord;\n"
    "out vec2 Texcoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 view;\n"
    "out vec3 Normal;\n"
    "out vec3 FragPos;\n"
    "void main()\n"
    "{\n"
    "    Texcoord = aTexCoord;"
    "    Normal = aNormal;\n"
    "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
    "    gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
    "}\n";

// shader source code
const char *fragmentSource =
        "#version 150 core\n"
        "in vec2 Texcoord;"
        "in vec3 Normal;"
        "in vec3 FragPos;"
        "out vec4 outColor;\n"
        "uniform vec3 objectColor;\n"
        "uniform vec3 lightColor;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 viewPos;\n"
        "void main()\n"
        "{\n"
        "   float ambientStrength = 0.1f;\n"
        "   vec3 norm = normalize(Normal);\n"
        "   vec3 lightDir = normalize(lightPos - FragPos);\n"
        "   float diff = max(dot(norm, lightDir), 0.0);"
        "   vec3 diffuse = diff * lightColor;\n"
        "   vec3 ambient = ambientStrength * lightColor;\n"
        "   float specularStrength = 0.9f;\n"
        "   vec3 viewDir = normalize(viewPos - FragPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, norm);\n"
        "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
        "   vec3 specular = specularStrength * spec * lightColor;\n"
        "   vec3 result = (ambient + diffuse + specular) * objectColor;\n"
        "   outColor = vec4(result, 1.0);\n"
        "}\n";

GLuint Box_InitShader() {
        // create a vertex shader and and pass source code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);

    // compile source code.
    glCompileShader(vertexShader);

    // compilation status for shader
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    // compile log
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

    printf("\n%s\n", buffer);
    // set the source code of shader.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // compile source code.
    glCompileShader(fragmentShader);

    // compilation status for shader
    GLint status2;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);

    // compile log
    char buffer2[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer2);

    // create program out of vertex and fragment shader.

    printf("\n%s\n", buffer2);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
