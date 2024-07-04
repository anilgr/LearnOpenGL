#include <stdlib.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "app/shader.h"
#include "box.c"

#define SUPPORT_FILEFORMAT_JPG

float getFrameTime(void);

int main()
{
    srand(time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CURSOR_HIDDEN, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(1080, 720, "OpenGL", NULL, NULL); // Windowed

    // crete opengl context.
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    float vertices[] = {
        // positions // normals // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    // generate vertex attribute array object (vao)
    GLuint Box_VAO;
    glGenVertexArrays(1, &Box_VAO);
    glBindVertexArray(Box_VAO);
    // generate array buffer (vbo) and store the integer pointer to it.
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // copy the above data to the arraybuffer that was binded before.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    App_Shader *boxShader = App_Shader_Load("box.vs", "box.fs"); 

    // get the shader attribute locs

    GLint aPos = glGetAttribLocation(boxShader->program, "aPos");

    GLint aNormal = glGetAttribLocation(boxShader->program, "aNormal");

    GLint aTexCoord = glGetAttribLocation(boxShader->program, "aTexCoord");

    glEnableVertexAttribArray(aPos);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), 0);

    glEnableVertexAttribArray(aNormal);
    glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(aTexCoord);
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void *)(6 * sizeof(float)));
    
    App_Shader_Use(boxShader);
    Matrix proj = MatrixPerspective(45.0f * DEG2RAD, 1080.0f / 720.0f, 1.0f, 100.0f);
    App_Shader_SetMatrix4f(boxShader, "proj", MatrixToFloatV(proj).v);
    App_Shader_SetVec3f(boxShader, "objectColor", (app_float3){ 1.0f, 0.5f, 0.0f });
    App_Shader_SetVec3f(boxShader, "lightColor", (app_float3){1.0f, 1.0f, 1.0f});
    App_Shader_SetVec3f(boxShader, "lightPos", (app_float3){ 2.0f, 2.0f, -2.0f });

    // generate vertex attribute array object (vao)
    GLuint Light_vao;
    glGenVertexArrays(1, &Light_vao);
    glBindVertexArray(Light_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    App_Shader *lightShader = App_Shader_Load("light.vs", "light.fs");

    GLint Light_aPos = glGetAttribLocation(lightShader->program, "aPos");
    
    glEnableVertexAttribArray(Light_aPos);
    glVertexAttribPointer(Light_aPos, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), 0);

    App_Shader_Use(lightShader);
    App_Shader_SetMatrix4f(lightShader, "proj", MatrixToFloatV(proj).v);

    Vector3 cameraPos = (Vector3){0.0f, 0.0f, 3.0f};
    Vector3 cameraFront = (Vector3){0.0f, 0.0f, -1.0f};
    Vector3 cameraUp = (Vector3){0.0f, 1.0f, 0.0f};
    double prevTimestamp = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double delta = glfwGetTime() - prevTimestamp;
        prevTimestamp = prevTimestamp + delta;

        const float cameraSpeed = 5.0f * delta; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos = Vector3Add(cameraPos, Vector3Scale(cameraFront, cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos = Vector3Subtract(cameraPos, Vector3Scale(cameraFront, cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos = Vector3Subtract(cameraPos, Vector3Scale(Vector3Normalize(Vector3CrossProduct(cameraFront, cameraUp)), cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos = Vector3Add(cameraPos, Vector3Scale(Vector3Normalize(Vector3CrossProduct(cameraFront, cameraUp)), cameraSpeed));

        double deltaYaw = 0.0f;
        double deltaPitch = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            deltaYaw = 1.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            deltaYaw = -1.0f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            deltaPitch = 1.0f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            deltaPitch = -1.0f;

        cameraFront = Vector3RotateByAxisAngle(cameraFront, cameraUp, (-1.0f * deltaYaw * 60.0f) * DEG2RAD * delta);
        Vector3 axs = Vector3Normalize(Vector3CrossProduct(cameraFront, cameraUp));
        cameraFront = Vector3RotateByAxisAngle(cameraFront, axs, (deltaPitch * 50.0f) * DEG2RAD * delta);
        // update view matrix
        Matrix view = MatrixLookAt(cameraPos, Vector3Add(cameraPos, cameraFront), cameraUp);
        App_Shader_Use(boxShader);
        App_Shader_SetMatrix4f(boxShader, "view", MatrixToFloatV(view).v);
        Matrix model = MatrixIdentity();
        model = MatrixMultiply(model, MatrixTranslate(0.0f, 0.0f, 0.0f));
        float angle = 90.0f * sin(glfwGetTime()/4.0f);
        Matrix boxModel = MatrixMultiply(model, MatrixRotate((Vector3){1.0f, 0.3f, 0.5f}, angle * DEG2RAD));
        App_Shader_SetMatrix4f(boxShader, "model", MatrixToFloatV(boxModel).v);
        App_Shader_SetVec3f(boxShader, "viewPos", Vector3ToFloat(cameraPos));
        double offset = 2.0f * sin(glfwGetTime());
        float pos[3] = { 1.5f, 2.0f + offset, -1.5f };
        App_Shader_SetVec3f(boxShader, "lightPos", pos);

        glBindVertexArray(Box_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        App_Shader_Use(lightShader);
        App_Shader_SetMatrix4f(lightShader, "view", MatrixToFloatV(view).v);
        Matrix lightModel = MatrixMultiply(model, MatrixScale(0.5f, 0.5f, 0.5f));
        lightModel = MatrixMultiply(lightModel, MatrixTranslate(1.5f, 2.0f + offset, -1.5f));
        App_Shader_SetMatrix4f(lightShader, "model", MatrixToFloatV(lightModel).v);
        
        glBindVertexArray(Light_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }

    glfwTerminate();
}
