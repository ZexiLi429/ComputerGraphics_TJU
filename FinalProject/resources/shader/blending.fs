#version 330 core
out vec4 FragColor; // 输出的片段颜色

in vec2 TexCoords; // 从顶点着色器传递来的纹理坐标

struct Light { 
    vec3 ambient; // 环境光
};

uniform Light light; // 光源结构体的实例

void main()
{             
    // 设置为雪白色
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // 雪白色
}
