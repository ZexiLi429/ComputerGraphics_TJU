#ifndef SNOWPARTICLE_H
#define SNOWPARTICLE_H

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "Shader.h" // ȷ������Shader���ͷ�ļ�

class SnowParticleSystem {
public:
    SnowParticleSystem(int maxParticles);
    void update(float deltaTime);
    void draw(Shader& shader); // �޸� draw ��������� Shader ����

private:
    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;
        float life; // ��������
    };

    std::vector<Particle> particles;
    int maxParticles;

    GLuint VAO, VBO; // VAO �� VBO
};

#endif
