#include "SnowParticle.h"
#include <cstdlib>
#include <iostream>

using namespace std;

SnowParticleSystem::SnowParticleSystem(int maxParticles)
    : maxParticles(maxParticles) {
    particles.resize(maxParticles);

    // 初始化粒子
    for (int i = 0; i < maxParticles; ++i) {
        particles[i].position = glm::vec3((rand() % 20000 - 10000) / 1.0f,
            (rand() % 1000) / 10.0f + 1000.0f,
            (rand() % 20000 - 10000) / 1.0f);
        particles[i].velocity = glm::vec3(0.0f, -0.1f - static_cast<float>(rand()) / RAND_MAX * 0.05f, 0.0f);
        particles[i].life = static_cast<float>(rand()) / RAND_MAX;
    }

    // 创建VAO和VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

}

void SnowParticleSystem::update(float deltaTime) {
    for (auto& particle : particles) {
        particle.position += particle.velocity * deltaTime;
        particle.life -= deltaTime; // 减少生命周期

        // 重置粒子
        if (particle.life <= 0.0f || particle.position.y < -5.0f) {
            particle.position.y = 100.0f; // 从顶部重新生成
            particle.position.x = static_cast<float>(rand() % 20001 - 10000);
            particle.position.z = static_cast<float>(rand() % 20001 - 10000);
            particle.life = static_cast<float>(rand()) / RAND_MAX; // 随机生命周期
        }
    }
}

void SnowParticleSystem::draw(Shader& shader) {
    glEnable(GL_BLEND); // 启用混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合函数
   

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 更新粒子数据
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);

    shader.use(); // 使用着色器
    glDrawArrays(GL_POINTS, 0, particles.size()); // 绘制粒子

    glBindVertexArray(0);
}
