#version 150 core
in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
void main() {
    TexCoords = aTexCoord;
    Normal = vec3(model * vec4(aNormal, 1.0));
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}
