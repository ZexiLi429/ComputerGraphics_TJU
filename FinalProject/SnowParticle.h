#ifndef SNOWPARTICLE_H
#define SNOWPARTICLE_H

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "Shader.h" // 确保包含Shader类的头文件

class SnowParticleSystem {
public:
    SnowParticleSystem(int maxParticles);
    void update(float deltaTime);
    void draw(Shader& shader); // 修改 draw 方法，添加 Shader 参数

private:
    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;
        float life; // 生命周期
    };

    std::vector<Particle> particles;
    int maxParticles;

    GLuint VAO, VBO; // VAO 和 VBO
};

#endif
