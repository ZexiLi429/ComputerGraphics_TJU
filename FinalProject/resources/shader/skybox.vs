#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // 新增：法线输入
out vec3 ReflectDir;//
out vec3 TexCoords;
out float time;

uniform float u_time;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 cameraPos; // 新增：相机位置的 uniform
void main()
{
    time = u_time;
 

    TexCoords = aPos;
    // 计算视线方向（从相机位置指向顶点）
    vec3 viewDir = normalize(cameraPos - aPos);
    // 计算反射向量
    ReflectDir = reflect(-viewDir, aNormal);
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  