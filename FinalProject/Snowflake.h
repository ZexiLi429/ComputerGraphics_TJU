#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> // ʹ��glad��

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
    GLuint VAO; // �����������
    GLuint VBO; // ���㻺��������

    void init(int count);
    void update(float deltaTime);
    void draw();
    void setupBuffers(); // ���û�����
};

#endif // SNOWFLAKE_H
