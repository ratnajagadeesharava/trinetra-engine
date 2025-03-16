#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;


uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 model;


uniform vec3 objColor;

out vec3 Normal;
out vec3 FragPos;
out vec3 fragColor;

void main()
{
    FragPos = vec3(model*vec4(aPos,1.0));
    fragColor = aPos;
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    // gl_Position = projection * viewMatrix * model * vec4(aPos, 1.0);
    gl_Position = vec4(aPos,1.0);

}
