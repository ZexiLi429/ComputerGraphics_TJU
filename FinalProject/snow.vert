#version 330 core

layout(location = 0) in vec3 inPosition; // 粒子位置

uniform mat4 mvp; // 模型视图投影矩阵
out float pointSize; // 输出到片段着色器的点大小

void main() {
    gl_Position = mvp * vec4(inPosition, 1.0); // 计算屏幕位置
    pointSize = 10.0; // 设置点的大小（可以根据需要调整）
    gl_PointSize = pointSize; // OpenGL中设置点的大小
}
