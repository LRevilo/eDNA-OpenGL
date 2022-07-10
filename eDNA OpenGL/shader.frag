#version 330 core
out vec4 FragColor;

in vec3 Normals;  
in vec2 TexCoords;
in vec3 FragPos;  

uniform sampler2D texture_diffuse1;

uniform vec4 color;
uniform vec4 ambientColor;
uniform vec4 directionalColor;
uniform vec3 directionalDir;

#define f length(fract(TC*=mat2(7, -5, 5, 7)*.1) - .5)

void main()
{    
    vec4 t = color;//texture(texture_diffuse1,TexCoords);

    float dir = max(dot(-directionalDir,Normals),0);
    vec4 c = ambientColor*(1.f-dir)+ color*dir;
    

    vec2 TC = TexCoords*5;

    FragColor += min(min(f, f), f)/.6 - FragColor;

    FragColor *= c*directionalColor;

}