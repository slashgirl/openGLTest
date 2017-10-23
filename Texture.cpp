#include "Texture.h"
//#include "ImageLoader/stb_image.h"
#include "SOIL/SOIL.h"
#include <iostream>

Texture::Texture(const std::string& fileName)	//构造函数:加载纹理图像
{
	//int width, height, numComponents;
	//unsigned char* data =stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);	//加载图像，会返回一个数据，用data来接收（用stb_image库来加载）
	//

	//if(data == NULL)
	//{
	//	std::cerr << "无法加载纹理" << fileName << std::endl;		//使程序更加严谨
	//}

	//glGenTextures(1, &m_texture);		//创建纹理标识

	//glBindTexture(GL_TEXTURE_2D, m_texture);		//使用二维纹理

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//对绑定的纹理进行参数的设定
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//如果需要填充的区域大于图片的大小时，使图片重复

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		//设置纹理参数,设置文理的过滤器为线性的
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);		//将纹理的数据传送至GPU

	//stbi_image_free(data);		//调用的data要释放掉





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
	glDeleteTextures(1, &m_texture);		//删除纹理(glGenTextures(1, &m_texture);		//创建纹理标识
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}