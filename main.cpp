#include <iostream>
#include "GL/glew.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[])
{
	Display display(800, 600, "hello openGL");
	
	Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0,0)),
						 Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(0,1)),
						 Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1,1)),
						 Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1,0))};		//������������

	unsigned int indices[] ={0,1,2,3};								//�����涨�˶����˳��
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
			  indices, sizeof(indices) / sizeof(indices[0]));		//����mesh����,��ֹ���ݶ������ݣ�Ҳ��������

	//Mesh mesh2("./res/monkey3.obj");
	Mesh mesh2("./res/test.obj");

	Shader shader("./res/basicShader");		//����һ��shader����,��shader֮���������

	//Texture texture("./res/bricks.jpg");	//����ļ���·��
	Texture texture("./res/Logo01.dds");	//dds����ļ���·��

	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

	Transform transform;
	float counter =0.1f;

	while (!display.IsClosed())		//���ڲ��ǹر�״̬
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter =sinf(counter);
		float cosCounter =cosf(counter);
		transform.GetPos() ->x =sinCounter;
		transform.GetRot() ->x =counter*0.5;
		transform.GetRot() ->z =counter*0.5;
		transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

		shader.Bind();

		shader.Update(transform, camera);

		mesh.Draw();
		//mesh2.Draw();

		display.Update();

		counter += 0.001f;
	}
	return 0;
}