#include "Snowflake.h"
#include <glad/glad.h> // ȷ��ʹ��GLAD����OpenGL����
#include <GLFW/glfw3.h>
#include <iostream>

Snowflake::Snowflake(float x, float y, float size, float speed)
    : position(x, y), size(size), speed(speed) {}

void Snowflake::fall(float deltaTime) {
    position.y -= speed * deltaTime;
    if (position.y < 0) {
        position.y = 1.0f; // ���õ�����
        position.x = static_cast<float>(rand()) / RAND_MAX; // ���xλ��
    }
}

void Snowfall::init(int count) {
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX;
        float y = static_cast<float>(rand()) / RAND_MAX;
        float size = (static_cast<float>(rand()) / RAND_MAX) * 0.05f + 0.01f; // �����С
        float speed = (static_cast<float>(rand()) / RAND_MAX) * 0.1f + 0.05f; // ����ٶ�
        snowflakes.emplace_back(x, y, size, speed);
    }

    setupBuffers(); // ��ʼ��������
}

void Snowfall::setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // ���û�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, snowflakes.size() * sizeof(Snowflake), nullptr, GL_DYNAMIC_DRAW);

    // �趨��������ָ��
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Snowflake), (GLvoid*)offsetof(Snowflake, position));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Snowfall::update(float deltaTime) {
    for (auto& snowflake : snowflakes) {
        snowflake.fall(deltaTime);
    }
}

void Snowfall::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, snowflakes.size());
    glBindVertexArray(0);
}
