

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <windows.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "skyboxcube.h"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "texture.h"
#include "LoadPlyModel.h"
#include <iostream>
#include <irrklang/irrKlang.h>
#include "bezier_surface.h"
#include "SnowParticle.h"

using namespace irrklang;







// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
bool light = false;
bool ball = false;
bool collision = false;
float rate = 0.01;
int rateCount = 0;
bool visible = true;
const int num_of_flag = 1;
const int flag_start_x = -0.5;
bool down = false;

// camera
Camera camera(glm::vec3(22.124243, 6.758541,8.0));

float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// show
int show = 0;

// bomb position
float bombx = 0.5, bomby = 3;







// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// Camera& camera---------------------------------------------------------------------------------------------------------

void processInput(GLFWwindow* window,  float deltaTime)

{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	camera.updateCameraVectors(); // 确保在移动后更新向量
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

glm::vec3 lightPos(1.0f, 7.2f, -0.6f);

float inter(float a, float b, float time, float interval);




//道路
vector<Model>roads;
vector<glm::vec3>road_pos;
vector<glm::vec3>road_rot;
vector<glm::vec3> road_scl;
void init_roads()
{

	//地面
	roads.push_back(Model("resources/objects/floor/flat-test.obj"));
	road_pos.push_back(glm::vec3(0, 0.85, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1000.0, 1.0, 1000.0));



	//道路
	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-90, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));
	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-60, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));
	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-30, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(0, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(30, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(60, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));
	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(90, 0, 0));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));


	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-90, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-60, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(-30, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(0, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(30, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(60, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));

	roads.push_back(Model("resources/objects/road/road2/untitled.obj"));
	road_pos.push_back(glm::vec3(90, 0, 4.3));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));



	//建筑
	/*
	roads.push_back(Model("resources/objects/house/medieval-house-2-obj/medieval-house-2.obj"));
	road_pos.push_back(glm::vec3(0, -2, -3.5));
	road_rot.push_back(glm::vec3(0, 0, 0));
	road_scl.push_back(glm::vec3(1.0, 1.0, 1.0));
	*/

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 004.obj"));
	road_pos.push_back(glm::vec3(-10, 5, 0));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 005.obj"));
	road_pos.push_back(glm::vec3(-10, 5, 30));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 008.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -20));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 008.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -55));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 002.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -85));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 001.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -115));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 003.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -145));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 002.obj"));
	road_pos.push_back(glm::vec3(-10, 5, -175));
	road_rot.push_back(glm::vec3(0, -90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));




	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 002.obj"));
	road_pos.push_back(glm::vec3(-11, 5, -60));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));


	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 007.obj"));
	road_pos.push_back(glm::vec3(-11, 5, -30));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));


	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 006.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 0));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));


	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 005.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 30));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 005.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 60));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 004.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 90));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 002.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 120));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 002.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 150));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));

	roads.push_back(Model("resources/objects/house/house2/Residential Buildings 004.obj"));
	road_pos.push_back(glm::vec3(-11, 5, 180));
	road_rot.push_back(glm::vec3(0, 90, 0));
	road_scl.push_back(glm::vec3(0.9, 0.9, 0.9));


	//旗杆

	for (int i = 0; i < num_of_flag; ++i)
	{
		roads.push_back(Model("resources/objects/roll/flag.obj"));
		road_pos.push_back(glm::vec3((float)(flag_start_x) / 20.0 + 0.2 * i, 0.06, -0.16));
		road_rot.push_back(glm::vec3(0, 0, 0));
		road_scl.push_back(glm::vec3(20.0, 20.0, 20.0));

		roads.push_back(Model("resources/objects/roll/flag.obj"));
		road_pos.push_back(glm::vec3((float)(flag_start_x) / 20.0 + 0.2 * i, 0.06, 0.32));
		road_rot.push_back(glm::vec3(0, 0, 0));
		road_scl.push_back(glm::vec3(20.0, 20.0, 20.0));
	}

}
void draw_roads(Shader shader)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
	//model = glm::rotate(model, glm::radians((float)glfwGetTime() * -40.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
	shader.setMat4("model", model);
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("lightPos", camera.Position);

	for (int i = 0; i < roads.size(); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, road_scl[i]);
		model = glm::rotate(model, glm::radians(road_rot[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(road_rot[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(road_rot[i].z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, road_pos[i]);

		shader.setMat4("model", model);
		shader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f)); // 雪白色

		roads[i].Draw(shader);
	}

}

float Bernstein(float t, int index)
{
	switch (index)
	{
	default:
	case 0:
		return pow(1.0 - t, 3);
		break;
	case 1:
		return 3 * t * pow(1.0 - t, 2);
		break;
	case 2:
		return 3 * pow(t, 2) * (1 - t);
		break;
	case 3:
		return pow(t, 3);
		break;
	}
}
float Bernstein4(float t, int index)
{
	switch (index)
	{
	default:
	case 0:
		return pow(1.0 - t, 4);
		break;
	case 1:
		return 4 * t * pow(1.0 - t, 3);
		break;
	case 2:
		return 6 * pow(t, 2) * pow(1 - t, 2);
		break;
	case 3:
		return 4 * pow(t, 3) * (1 - t);
		break;
	case 4:
		return pow(t, 4);
		break;
	}
}



vector<Model>tanks;
vector<glm::vec3>tank_pos;
vector<glm::vec3>tank_rot;
vector<glm::vec3> tank_scl;
vector<glm::vec3> tank_move;
void init_tanks()
{
	tanks.push_back(Model("resources/objects/tank/german-panzer-ww2-ausf-b-obj/german-panzer-ww2-ausf-b.obj"));
	tank_pos.push_back(glm::vec3(0, 100, -3));
	tank_rot.push_back(glm::vec3(0, -90, 0));
	tank_scl.push_back(glm::vec3(0.02, 0.02, 0.02));
	tank_move.push_back(glm::vec3(0, 0, 0));
}

void draw_tanks(Shader shader, float time)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("lightPos", camera.Position);

	for (int i = 0; i < tanks.size(); ++i)
	{

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, tank_scl[i]);
		model = glm::rotate(model, glm::radians(tank_rot[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(tank_rot[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(tank_rot[i].z), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec3 trans = tank_pos[i];

		trans.x += tank_move[i].x * time;
		trans.y += tank_move[i].y * time;
		trans.z += tank_move[i].z * time;
		model = glm::translate(model, trans);

		shader.setMat4("model", model);
		tanks[i].Draw(shader);
	}

}


vector<glm::vec3>air_lines;
vector<glm::vec3> controll_points = { {-74.026802,6.420523,5.043897},//路径的起始点
										{70.869812,60.382334,10.163822},
										{70.804667,50.744003,-30.531231},
										{-74.804667,30.744003,-70.531231},
										{-74.026802,24.420523,5.043897} };
/*
vector<glm::vec3> controll_points = { {-74.026802,7.420523,5.043897},//路径的起始点
										{100.869812,4.382334,18.163822},
										{100.804667,4.744003,-70.531231},
										{-74.804667,30.744003,-70.531231},
										{-74.026802,24.420523,5.043897} };
*/
const int prec = 100000;
void init_bezier()
{
	int len = controll_points.size();
	for (int i = 0; i <= prec; i++)
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float u = (float)i / prec;
		for (int i = 0; i < len; i++)
		{
			int index = i;
			if (len == 4)
			{
				x += controll_points[index].x * Bernstein(u, i);
				y += controll_points[index].y * Bernstein(u, i);
				z += controll_points[index].z * Bernstein(u, i);
			}
			if (len == 5)
			{
				x += controll_points[index].x * Bernstein4(u, i);
				y += controll_points[index].y * Bernstein4(u, i);
				z += controll_points[index].z * Bernstein4(u, i);
			}
		}
		air_lines.push_back({ x,y,z });
	}
}


vector<Model>planes;
vector<glm::vec3>plane_pos;
vector<glm::vec3>plane_rot;
vector<glm::vec3> plane_scl;
vector<glm::vec3> plane_move;
vector<glm::vec3> plane_last_pos;
vector<glm::vec3>plane_last_dir;
void init_planes()
{
	planes.push_back(Model("resources/objects/plane/plane2/F-16D.obj"));

	plane_pos.push_back(glm::vec3(0, 3, 0));
	plane_rot.push_back(glm::vec3(0, 90, 0));
	plane_scl.push_back(glm::vec3(0.08, 0.08, 0.08));
	plane_move.push_back(glm::vec3(0, 0, 0));
	plane_last_pos.push_back(glm::vec3(0, 0, 0));


	init_bezier();
}

vector<BezierFace>flags;
vector<glm::vec3>flag_pos;
vector<float>flag_x;
void init_flag()
{
	float flag_controll_points[] = {
	 0, 0, 0,     0, 0, 1.5,     0, 0, 3.0,    0, 0,4.5 ,   0,0,6,
	 0, 1, 0,     0, 1, 1.5,     0, 1, 3.0,    0, 1,4.5 ,	0,1,6 ,
	 0, 2, 0,     0, 2, 1.5,     0, 2, 3.0,    0, 2,4.5 ,   0,2,6,
	 0, 3, 0,     0, 3, 1.5,     0, 3, 3.0,    0, 3,4.5 ,   0,3,6,
	 0, 4, 0,     0, 4, 1.5,     0, 4, 3.0,    0, 4,4.5 ,	0,4,6
	};


	for (int i = 0; i < num_of_flag; ++i)
	{
		flags.push_back(BezierFace(4, flag_controll_points, 100, "resources/textures/flag.png", 5, 5));
		flag_pos.push_back({ flag_start_x + 4.0 * i,5.0, -1.0});
		flag_x.push_back(flag_start_x + 4.0 * i);
		
		flags.push_back(BezierFace(4, flag_controll_points, 100, "resources/textures/flag.png", 5, 5));
		flag_pos.push_back({ flag_start_x + 4.0 * i,5.0,1.0});
		flag_x.push_back(flag_start_x + 4.0 * i);
	}
}
void draw_flags(Shader flag_shader, float time)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	flag_shader.use();
	flag_shader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
	flag_shader.setVec3("viewPos", camera.Position);
	// light properties
	flag_shader.setVec3("light.ambient", 0.8f, 0.8f, 0.8f);
	flag_shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	flag_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	flag_shader.setFloat("material.shininess", 32.0f);
	flag_shader.setMat4("projection", projection);
	flag_shader.setMat4("view", view);
	flag_shader.setVec3("lightPos", camera.Position);
	flag_shader.setFloat("time", time);
	for (int i = 0; i < flags.size(); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, flag_pos[i]);
		model = glm::scale(model, { 0.5,0.5,0.5 });
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		flag_shader.setMat4("model", model);
		flag_shader.setFloat("center_x", flag_x[i]);
		flags[i].draw(flag_shader);
	}
}


void draw_planes(Shader shader, float time)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("lightPos", camera.Position);

	for (int i = 0; i < planes.size(); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);



		glm::vec3 lastPos = plane_last_pos[i];
		glm::vec3 nowPos = plane_pos[i];
		int idx = (int)(time * 8000.0) % air_lines.size();
		nowPos += air_lines[idx];
		model = glm::translate(model, nowPos);
		glm::vec3 dir = nowPos - lastPos;
		float ang_rad = atan2(-dir.z, dir.x);
		model = glm::rotate(model, ang_rad, glm::vec3(0.0f, 1.0f, 0.0f));


		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(plane_rot[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
		float omiga = 1.5;
		if (1.5 <= time && time <= 1.5 + (2.0f * 3.1415926f) / omiga / 4.0f)
			model = glm::rotate(model, 2.0f * 3.14159265f * sin((time - 1.5f) * omiga), glm::vec3(0.0f, 0.0f, 1.0f));
		float time2 = 1.5 + (2.0f * 3.1415926f) / omiga / 4.0f;
		float time3 = time2 + 1.0;
		float time4 = time3 + 3.0;
		float time5 = time4 + 1.0;
		if (time2 <= time && time <= time3)
			model = glm::rotate(model, (time - time2) / (time3 - time2) * -3.1415926f / 2.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		if (time3 <= time && time <= time4)
			model = glm::rotate(model, -3.1415926f / 2.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		if (time4 <= time && time <= time5)
			model = glm::rotate(model, (time - time4) / (time5 - time4) * 3.1415926f / 2.5f + -3.141526f / 2.5f, glm::vec3(0.0f, 0.0f, 1.0f));



		//printf("%f,%f,%f\n", dir.x, dir.y, dir.z);
		model = glm::scale(model, plane_scl[i]);
		shader.setMat4("model", model);
		planes[i].Draw(shader);
		plane_last_pos[i] = nowPos;

	}

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------

	Shader skyboxShader("resources/shader/skybox.vs", "resources/shader/skybox.fs");
	Skybox skybox(0);
	Shader skyboxShader1("resources/shader/skybox1.vs", "resources/shader/skybox1.fs");
	Skybox skybox1(1);
	Shader floorShader("resources/shader/blending.vs", "resources/shader/blending.fs");
	Shader wallShader("resources/shader/wall.vs", "resources/shader/wall.fs");
	Shader lightingShader("resources/shader/light_casters.vs", "resources/shader/light_casters.fs");
	floorShader.use();
	floorShader.setInt("texture1", 0);

	Model rock("resources/objects/rock/rock.obj");
	Model bomb("resources/objects/Bomb/Bomb.obj");

	Model terracotta1("resources/objects/statue/12339_statue_v2_l1.obj");
	Model terracotta2("resources/objects/statue/12340_statue_v2_l1.obj");
	Model terracotta3("resources/objects/statue/12341_Statue_v2_l1.obj");

	unsigned int diffuseMap = loadTexture("resources/textures/brickwall.jpg");
	unsigned int normalMap = loadTexture("resources/textures/brickwall_normal.jpg");

	unsigned int floorTexture = loadTexture("resources/textures/brickwall.jpg");
	unsigned int floorNormalTexture = loadTexture("resources/textures/brickwall_normal.jpg");

	wallShader.use();
	wallShader.setInt("diffuseMap", 0);
	wallShader.setInt("normalMap", 1);


	//阿布
	init_roads();
	init_tanks();
	init_planes();
	Shader parallelShader("resources/shader/parallel.vs", "resources/shader/parallel.fs");
	Shader flagShader("resources/shader/flag.vs", "resources/shader/parallel.fs");
	init_flag();

	Shader shader("snow.vert", "snow.frag"); // 假设已定义路径
	//GLuint shaderProgram = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl"); // 自定义的加载着色器函数



// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
	//float fogColor[] = { 1,1,1,1 };

		// lights
	// ------


	// initialize static shader uniforms before rendering
	// --------------------------------------------------
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


	float startTime = glfwGetTime();
	float time;
	float alpha = 0;
	float time1 = 0;

	float planeVertices[] = {
		// positions          // texture Coords 
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	// plane VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	unsigned int amount = 100;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	float radius = 10.0;
	float offset = 2.5f;
	float x = 0, y = -0.5, z = -4.5;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		x += 0.1;
		if (i % 10 == 0)
		{
			y += 0.1;
			x = 0;
		}
		model = glm::translate(model, glm::vec3(x, y, z));
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		modelMatrices[i] = model;
	}

	show = 0;
	// 在适当的位置初始化雪花粒子系统


	float lastFrame = 0.0f; // 前一帧时间
	const int maxParticles = 1000; // 最大粒子数
	SnowParticleSystem snowParticleSystem(maxParticles);
	
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		time = currentFrame - startTime;
		float cameraSpeed = 2.5f * deltaTime;

		// input
		// -----
		//processInput(window);
		processInput(window,  deltaTime);
		//processKeyboardInput(window, cameraPos, cameraFront, cameraUp, cameraSpeed);
		// render
		// ------
	




		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// 更新雪花粒子
		snowParticleSystem.update(deltaTime);
		// 计算视图矩阵

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 mvp = projection * view; // 计算MVP矩阵

		// 在绘制雪花之前设置MVP矩阵
		shader.use();
		shader.setMat4("mvp", mvp); // 设置MVP矩阵
		snowParticleSystem.draw(shader);
		//glm::mat4 view = camera.GetViewMatrix(); 
		glm::mat4 model = glm::mat4(1.0f);
		// 计算视图和投影矩阵
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);





		if (show == 0)
		{
			//camera.Position = glm::vec3(22.124243, 6.758541, 0.0);
			//设置并使用平行光着色器
			parallelShader.use();
			parallelShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
			parallelShader.setVec3("viewPos", camera.Position);
			// 光照属性
			parallelShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
			parallelShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			parallelShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
			// 材质属性
			parallelShader.setFloat("material.shininess", 32.0f);
			//draw_roads(parallelShader);


			draw_tanks(parallelShader, time
			);
/*
			if (time <= 4.0f)
			{
				glm::vec3 p1 = { 13.748635 - 1.0f,2.143705 - 8.0f,-8.0f };
				glm::vec3 p2 = { 13.748635 - 1.0f,15.143705 - 8.0f,-8.0f };
				glm::vec3 p = p1 + time * (p2 - p1) / 4.0f;
				camera.Front = p - camera.Position;
			}
			if (4.0f <= time && time < 9.0f)
			{
				glm::vec3 p1 = { 13.748635,15.143705 - 3.0f,-3.0f };
				glm::vec3 p2 = controll_points[0];
				glm::vec3 p = p1 + 0.8f * (time - 4.0f) * (p2 - p1) / 3.0f;
				camera.Front = p - camera.Position;
			}
			if (9.0f <= time && time < 19.0f)
			{
				draw_planes(parallelShader, time - 7.0);
				camera.Front = plane_last_pos[0] - camera.Position;
			}
			else if (19.0f <= time && time < 30.0f)
			{
				camera.Position = glm::vec3(22.124243, 6.758541, 0.0);
				camera.Front = glm::vec3(70, 0, -2);
			}
			else if (time >= 30.0f)
			{
				// 在这里添加结束的逻辑
				camera.Front = glm::vec3(0, 0, 0); // 停止更新前方方向
				// 其他必要的清理或结束逻辑
			}
*/


			draw_flags(flagShader, time);

			//绘制天空盒（添加 Environment Mapping 设置）
			skyboxShader.use();
			// 传递相机位置用于反射计算
			skyboxShader.setVec3("cameraPos", camera.Position);
			view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
			//projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_WIDTH, 0.1f, 100.0f);
			skyboxShader.setMat4("view", view);
			skyboxShader.setMat4("projection", projection);

			//u_time代表亮度貌似
			skyboxShader.setFloat("u_time", 0);//0
			skybox.Draw();

		}





		glDepthFunc(GL_LESS); // set depth function back to default

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

float inter(float a, float b, float time, float interval)
{
	float tmp = ((b - a) / interval) * time + a;
	if (a < b)
		return tmp > b ? b : tmp;
	else
		return tmp > a ? a : tmp;

}