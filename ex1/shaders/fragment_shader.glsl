#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform bool isSun;

void main()
{
    if (isSun) {
        // 太阳自发光
        FragColor = vec4(objectColor, 1.0);
    } else {
        // 环境光 - 增强环境光让行星更明亮
        float ambientStrength = 0.75;
        vec3 ambient = ambientStrength * vec3(1.0, 1.0, 0.9);

        // 漫反射
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.5, 1.5, 1.4); // 增强漫反射

        // 镜面反射
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 0.9);

        // 距离衰减 - 减弱衰减效果
        float distance = length(lightPos - FragPos);
        float attenuation = 1.0 / (1.0 + 0.005 * distance + 0.0001 * distance * distance);

        vec3 result = (ambient + (diffuse + specular) * attenuation) * objectColor;
        FragColor = vec4(result, 1.0);
    }
}
