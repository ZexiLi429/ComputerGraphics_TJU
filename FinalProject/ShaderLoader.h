#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>  // 确保你也包含GLFW


#include <string>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif // SHADER_LOADER_H
