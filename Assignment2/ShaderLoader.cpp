#include "ShaderLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>  // 确保你也包含GLFW
using namespace std;
// 用于编译着色器并检查错误
GLuint CompileShader(GLenum shaderType, const std::string& source) {
    GLuint shader = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // 检查编译错误
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // 在这里我们分配一个缓冲区以存储错误日志
       // std::vector<char> errorLog(maxLength);
       // glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        // 然后删除着色器对象
        glDeleteShader(shader);

        // 打印错误日志
       // std::cerr << "Shader compilation failed: " << &errorLog[0] << std::endl;
        return 0;
    }

    return shader;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // 读取顶点着色器代码
    std::ifstream vertexFile(vertex_file_path);
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexCode = vertexStream.str();

    // 读取片段着色器代码
    std::ifstream fragmentFile(fragment_file_path);
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentCode = fragmentStream.str();

    // 编译着色器
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // 创建程序并链接着色器
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // 删除着色器，因为它们现在已经被链接
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
