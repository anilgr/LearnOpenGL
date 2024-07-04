#version 150 core
in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;
out vec2 Texcoord;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
out vec3 Normal;
out vec3 FragPos;
void main()
{
    Texcoord = aTexCoord;
    Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = proj * view * model * vec4(aPos, 1.0);
};
