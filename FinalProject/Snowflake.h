#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> // 使用glad库

class Snowflake {
public:
    glm::vec2 position;
    float size;
    float speed;

    Snowflake(float x, float y, float size, float speed);
    void fall(float deltaTime);
};

class Snowfall {
public:
    std::vector<Snowflake> snowflakes;
    GLuint VAO; // 顶点数组对象
    GLuint VBO; // 顶点缓冲区对象

    void init(int count);
    void update(float deltaTime);
    void draw();
    void setupBuffers(); // 设置缓冲区
};

#endif // SNOWFLAKE_H
