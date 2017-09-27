#include <iostream>
#include "GL/glew.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"

int main(int argc, char *argv[])
{
	Display display(800, 600, "hello openGL");
	
	Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0)),Vertex(glm::vec3(0, 0.5, 0)),Vertex(glm::vec3(0.5, -0.5, 0))};		//创建顶点数组

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));		//创建mesh对象

	Shader shader("./res/basicShader");		//创建一个shader对象

	while (!display.IsClosed())		//窗口不是关闭状态
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();

		mesh.Draw();

		display.Update();
	}
	return 0;
}