#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // ��������������
out vec3 ReflectDir;//
out vec3 TexCoords;
out float time;

uniform float u_time;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 cameraPos; // ���������λ�õ� uniform
void main()
{
    time = u_time;
 

    TexCoords = aPos;
    // �������߷��򣨴����λ��ָ�򶥵㣩
    vec3 viewDir = normalize(cameraPos - aPos);
    // ���㷴������
    ReflectDir = reflect(-viewDir, aNormal);
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  