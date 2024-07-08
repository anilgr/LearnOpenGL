#version 150 core
in vec3 aPos;
in vec3 aNormal;
in vec3 aTexCoord;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}