#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>  // ȷ����Ҳ����GLFW


#include <string>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif // SHADER_LOADER_H
