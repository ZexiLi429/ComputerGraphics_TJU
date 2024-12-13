#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform samplerCube skybox; // ʹ����պ���������ͼ

void main() {
    vec3 I = normalize(FragPos - viewPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = texture(skybox, R); // ��ȡ���䷽���ϵ���ɫ
}
