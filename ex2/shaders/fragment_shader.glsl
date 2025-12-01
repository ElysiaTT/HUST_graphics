#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// 纹理
uniform sampler2D texture1;
uniform bool useTexture;

// 光照
uniform vec3 sunLightPos;      // 太阳主光源位置
uniform vec3 backLightPos;     // 太阳背光位置
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform bool isSun;

void main()
{
    if (isSun) {
        // 太阳自发光，带纹理
        vec3 sunColor = objectColor;
        if (useTexture) {
            vec3 texColor = texture(texture1, TexCoord).rgb;
            sunColor = texColor * objectColor;
        }
        FragColor = vec4(sunColor, 1.0);
    } else {
        // 获取基础颜色
        vec3 baseColor = objectColor;
        if (useTexture) {
            baseColor = texture(texture1, TexCoord).rgb;
        }

        // 环境光
        float ambientStrength = 0.15;
        vec3 ambient = ambientStrength * vec3(1.0, 1.0, 0.95);

        // === 主光源（来自太阳） ===
        vec3 norm = normalize(Normal);
        vec3 sunLightDir = normalize(sunLightPos - FragPos);

        // 漫反射
        float sunDiff = max(dot(norm, sunLightDir), 0.0);
        vec3 sunDiffuse = sunDiff * vec3(1.8, 1.8, 1.7);

        // 镜面反射
        float specularStrength = 0.4;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-sunLightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 sunSpecular = specularStrength * spec * vec3(1.0, 1.0, 0.95);

        // 距离衰减
        float distance = length(sunLightPos - FragPos);
        float attenuation = 1.0 / (1.0 + 0.003 * distance + 0.00005 * distance * distance);

        vec3 sunContribution = (sunDiffuse + sunSpecular) * attenuation;

        // === 背光（专门照亮太阳） ===
        vec3 backLightDir = normalize(backLightPos - FragPos);
        float backDiff = max(dot(norm, backLightDir), 0.0);
        vec3 backDiffuse = backDiff * vec3(0.3, 0.3, 0.3); // 较弱的背光

        float backDistance = length(backLightPos - FragPos);
        float backAttenuation = 1.0 / (1.0 + 0.005 * backDistance + 0.0001 * backDistance * backDistance);

        vec3 backContribution = backDiffuse * backAttenuation;

        // 合成最终颜色
        vec3 result = (ambient + sunContribution + backContribution) * baseColor;
        FragColor = vec4(result, 1.0);
    }
}
