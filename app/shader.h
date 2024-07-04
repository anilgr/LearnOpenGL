#ifndef APP_SHADER_H
#define APP_SHADER_H

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

typedef struct App_Shader{
    GLuint program;
} App_Shader;

App_Shader* App_Shader_Load(char *vsFileName, char *fsFileName) {

    const char *vertexSource = readText(vsFileName);
    const char *fragmentSource = readText(fsFileName);

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
    //glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // get the shader attribute locs
    App_Shader *shader = (App_Shader*)malloc(sizeof(App_Shader));
    shader->program = shaderProgram;

    return shader;
}

void App_Shader_Use(App_Shader *shader) {
    glUseProgram(shader->program);
}

void App_Shader_SetMatrix4f(App_Shader *shader, char* uniform,  float matrix[16]) {
    glUniformMatrix4fv(glGetUniformLocation(shader->program, uniform), 1, GL_FALSE, matrix);
}

void App_Shader_SetVec3f(App_Shader *shader, char* uniform, float vec[3]) {
    glUniform3fv(glGetUniformLocation(shader->program, uniform), 1, vec);
}

#endif