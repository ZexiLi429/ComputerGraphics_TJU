#include "ShaderLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>  // ȷ����Ҳ����GLFW
using namespace std;
// ���ڱ�����ɫ����������
GLuint CompileShader(GLenum shaderType, const std::string& source) {
    GLuint shader = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // ���������
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // ���������Ƿ���һ���������Դ洢������־
       // std::vector<char> errorLog(maxLength);
       // glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        // Ȼ��ɾ����ɫ������
        glDeleteShader(shader);

        // ��ӡ������־
       // std::cerr << "Shader compilation failed: " << &errorLog[0] << std::endl;
        return 0;
    }

    return shader;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // ��ȡ������ɫ������
    std::ifstream vertexFile(vertex_file_path);
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexCode = vertexStream.str();

    // ��ȡƬ����ɫ������
    std::ifstream fragmentFile(fragment_file_path);
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentCode = fragmentStream.str();

    // ������ɫ��
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // ��������������ɫ��
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // ɾ����ɫ������Ϊ���������Ѿ�������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
