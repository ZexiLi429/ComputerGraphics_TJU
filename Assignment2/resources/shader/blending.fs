#version 330 core
out vec4 FragColor; // �����Ƭ����ɫ

in vec2 TexCoords; // �Ӷ�����ɫ������������������

struct Light { 
    vec3 ambient; // ������
};

uniform Light light; // ��Դ�ṹ���ʵ��

void main()
{             
    // ����Ϊѩ��ɫ
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // ѩ��ɫ
}
