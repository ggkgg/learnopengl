#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Shader.h"

#include<iostream>
using namespace std;
void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void preocessInput(GLFWwindow *window);

int main() {


	glfwInit();//��ʼ��GLFW

	//����GLFW������1����Ҫ���õ�ѡ�����2��ѡ��ֵ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ

	//��������
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//��ɣ��������еĴ��ڡ�cursor

		return -1;
	}

	//����������
	glfwMakeContextCurrent(window);


	//GLAD����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//�������ڵ����Ļص�����
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	float vertices[] = {
		//position         //color 
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2//��һ��������
	};

	Shader myShader("shader2_exercise2.vs", "shader1.fs");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//ʹ�ô��ڲ������Ϲر�
	while (!glfwWindowShouldClose(window))//���˴����Ƿ�Ҫ��ر�
	{
		preocessInput(window);//��������


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//������Ⱦ��ָ�����
		//...
		glBindVertexArray(VAO);
		float horizontalOffset = sin(glfwGetTime());
		cout << horizontalOffset << endl;
		myShader.setFloat("horizontalOffset", horizontalOffset);
		myShader.use();




		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		

		glfwSwapBuffers(window);//����color buffer
		glfwPollEvents();//�����Ƿ����κ��¼�������������������룬����ƶ������´���״̬�������ö�Ӧ�ĺ���
	}


	glfwTerminate();//���ٷ�����ڴ�ռ�



	return 0;
}
//�ص�����
void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


void preocessInput(GLFWwindow *window) {
	/*
	 * ����������Esc�������˳�ѭ�����رմ���;
	 * ������ǵĻ���glfwGetKey�᷵��GLFW_RELEASE
	 */
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}