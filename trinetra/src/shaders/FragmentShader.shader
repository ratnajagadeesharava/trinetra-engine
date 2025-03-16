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
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
     // Ambient lighting
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*lightColor;

    //Specular lighting
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos -FragPos);
    vec3 reflectDir  = reflect(-lightDir,norm);
    float spec = pow(max(0.0, dot(reflectDir, viewDir)), 32);

    vec3 specular = lightColor*specularStrength*spec;
    vec3 result = (specular+diffuse+ambient)*objectColor;

    FragColor = vec4(0,0,1.0, 1.0);

}
