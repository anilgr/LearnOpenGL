#include <stdlib.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "util.h"
// shader source code

// typedef struct Shader

GLuint Light_InitShader(void)
{

    const char *lightVertexSource = readText("light.vs");
    const char *lightFragmentSource = readText("light.fs");
    // printf("%s", lightFragmentSourceBk);

    // create a vertex shader and and pass source code
    GLuint lightVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lightVertexShader, 1, &lightVertexSource, NULL);

    // compile source code.
    glCompileShader(lightVertexShader);

    // compilation status for shader
    GLint status;
    glGetShaderiv(lightVertexShader, GL_COMPILE_STATUS, &status);

    // compile log
    char buffer[512];
    glGetShaderInfoLog(lightVertexShader, 512, NULL, buffer);

    printf("\n%s\n", buffer);

    // set the source code of shader.
    GLuint lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lightFragmentShader, 1, &lightFragmentSource, NULL);

    // compile source code.
    glCompileShader(lightFragmentShader);

    // compilation status for shader
    GLint status2;
    glGetShaderiv(lightFragmentShader, GL_COMPILE_STATUS, &status2);

    // compile log
    char buffer2[512];
    glGetShaderInfoLog(lightFragmentShader, 512, NULL, buffer2);

    // create program out of vertex and fragment shader.

    printf("\n%s\n", buffer2);

    GLuint lightShaderProgram = glCreateProgram();
    glAttachShader(lightShaderProgram, lightVertexShader);
    glAttachShader(lightShaderProgram, lightFragmentShader);

    glLinkProgram(lightShaderProgram);
    //glUseProgram(lightShaderProgram);

    glDeleteShader(lightVertexShader);
    glDeleteShader(lightFragmentShader);

    // get the shader attribute locs

    return lightShaderProgram;
}