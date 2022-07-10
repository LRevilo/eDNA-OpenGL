#version 330 core
out vec4 FragColor;

in vec3 Normals;  
in vec2 TexCoords;
in vec3 FragPos;  


uniform vec3 lightPos;

uniform sampler2D texture_diffuse1;

void main()
{    

    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float lightDis = length(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*vec3(1.f,1.f,1.f);
    vec3 result = (vec3(0.2f,0.2f,0.2f) + diffuse) * vec3(1.0f,0.5f,0.5f);

    vec2 c = 2.f*TexCoords - 1.f;
    float circle = c.x*c.x + c.y*c.y;

    FragColor = vec4(result,1.f);

}