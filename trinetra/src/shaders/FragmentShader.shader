#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 fragColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
out vec4 FragColor;
void main()
{
    

    FragColor = vec4(fragColor, 1.0);
}
