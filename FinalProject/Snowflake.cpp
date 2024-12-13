#include "Snowflake.h"
#include <glad/glad.h> // 确保使用GLAD加载OpenGL函数
#include <GLFW/glfw3.h>
#include <iostream>

Snowflake::Snowflake(float x, float y, float size, float speed)
    : position(x, y), size(size), speed(speed) {}

void Snowflake::fall(float deltaTime) {
    position.y -= speed * deltaTime;
    if (position.y < 0) {
        position.y = 1.0f; // 重置到顶部
        position.x = static_cast<float>(rand()) / RAND_MAX; // 随机x位置
    }
}

void Snowfall::init(int count) {
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX;
        float y = static_cast<float>(rand()) / RAND_MAX;
        float size = (static_cast<float>(rand()) / RAND_MAX) * 0.05f + 0.01f; // 随机大小
        float speed = (static_cast<float>(rand()) / RAND_MAX) * 0.1f + 0.05f; // 随机速度
        snowflakes.emplace_back(x, y, size, speed);
    }

    setupBuffers(); // 初始化缓冲区
}

void Snowfall::setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // 设置缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, snowflakes.size() * sizeof(Snowflake), nullptr, GL_DYNAMIC_DRAW);

    // 设定顶点属性指针
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
