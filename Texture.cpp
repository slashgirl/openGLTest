#include "Texture.h"
//#include "ImageLoader/stb_image.h"
#include "SOIL/SOIL.h"
#include <iostream>

Texture::Texture(const std::string& fileName)	//���캯��:��������ͼ��
{
	//int width, height, numComponents;
	//unsigned char* data =stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);	//����ͼ�񣬻᷵��һ�����ݣ���data�����գ���stb_image�������أ�
	//

	//if(data == NULL)
	//{
	//	std::cerr << "�޷���������" << fileName << std::endl;		//ʹ��������Ͻ�
	//}

	//glGenTextures(1, &m_texture);		//���������ʶ

	//glBindTexture(GL_TEXTURE_2D, m_texture);		//ʹ�ö�ά����

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//�԰󶨵�������в������趨
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//�����Ҫ�����������ͼƬ�Ĵ�Сʱ��ʹͼƬ�ظ�

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		//�����������,��������Ĺ�����Ϊ���Ե�
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);		//����������ݴ�����GPU

	//stbi_image_free(data);		//���õ�dataҪ�ͷŵ�





	//int width, height, numComponents;
	m_texture = SOIL_load_OGL_texture((fileName).c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS  
                                   //| SOIL_FLAG_MULTIPLY_ALPHA  
                                   //| SOIL_FLAG_COMPRESS_TO_DXT  
                                   | SOIL_FLAG_DDS_LOAD_DIRECT  
                                   //| SOIL_FLAG_NTSC_SAFE_RGB  
                                   //| SOIL_FLAG_CoCg_Y  
                                   //| SOIL_FLAG_TEXTURE_RECTANGLE  
                                  ); 

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);		//ɾ������(glGenTextures(1, &m_texture);		//���������ʶ
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}