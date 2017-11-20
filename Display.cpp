#include "Display.h"
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);	//初始化所有SDL要初始化的内容

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//设置颜色通道集
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//色值总共占4x8=32
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		//深度值(三维模型)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//设置双重缓冲区，便于实现内存交换

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);	//通过此项实现GPU到窗口的显示
	//以上SDL配置完成

	GLenum status = glewInit();  //初始化Glew
	if(status != GLEW_OK){
		std::cerr << "Glew Init failure" << std::endl;
	}

	m_isClosed = false;		//初始化为false
	m_bLeftButtonDown = false;
	m_bMidButtonDown = false;
	m_bRightButtonDown = false;
	m_sPreMousePosX = 0x7fffffff;
	m_sPreMousePosY = 0x7fffffff;

	glEnable(GL_DEPTH_TEST);	//激活深度值

}
Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update(Camera &curCamera, const AABB3 &bbModel)
{
	SDL_GL_SwapWindow(m_window);	//添加窗口

	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT: //关闭SDL窗口的时候
				m_isClosed = true;
				break;
			case SDL_MOUSEWHEEL: //滚轮前进后退
				{
					glm::vec3 curPos; glm::vec3 curFoword; glm::vec3 curUp;
					curCamera.GetCameraLocation(curPos, curFoword, curUp);
					glm::vec3 vModelCenter =(bbModel.minPos+bbModel.maxPos)/2.0f;
					float fDist =glm::length(curPos-vModelCenter); float fWalkLen =fDist*0.15f;
					glm::vec3 vDir =glm::normalize(vModelCenter-curPos);
					if(e.wheel.y == 1)
					{
						curPos +=vDir*fWalkLen;
					}else if(e.wheel.y == -1)
					{
						curPos -=vDir*fWalkLen;
					}
					curCamera.SetCameraLocation(curPos, curFoword, curUp);
				}
				break;
			case SDL_MOUSEBUTTONDOWN: //鼠标按键按下
				{
					if(e.button.button == SDL_BUTTON_LEFT) //如果是左键按下
					{ 
						m_bLeftButtonDown = true;
						m_sPreMousePosX = e.button.x;
						m_sPreMousePosY = e.button.y;
					}else if(e.button.button == SDL_BUTTON_MIDDLE)
				    {
						m_bMidButtonDown = true;
						m_sPreMousePosX = e.button.x;
						m_sPreMousePosY = e.button.y;
					}else if(e.button.button == SDL_BUTTON_RIGHT)
					{
						m_bRightButtonDown = true;
						m_sPreMousePosX = e.button.x;
						m_sPreMousePosY = e.button.y;
					}else
					{
					
					}
				}break;
			case SDL_MOUSEBUTTONUP: //鼠标松开
				{
					if(e.button.button == SDL_BUTTON_LEFT) //如果是左键松开
					{ 
						m_bLeftButtonDown = false;
						m_sPreMousePosX = 0x7fffffff;
						m_sPreMousePosY = 0x7fffffff;
					}else if(e.button.button == SDL_BUTTON_MIDDLE)
				    {
						m_bMidButtonDown = false;
						m_sPreMousePosX = 0x7fffffff;
						m_sPreMousePosY = 0x7fffffff;
					}else if(e.button.button == SDL_BUTTON_RIGHT)
					{
						m_bRightButtonDown = false;
						m_sPreMousePosX = 0x7fffffff;
						m_sPreMousePosY = 0x7fffffff;
					}else
					{
					
					}
				}break;
			case SDL_MOUSEMOTION: //鼠标移动
				{
					Sint32 iMouseMotionX = 0; Sint32 iMouseMotionY = 0; 
					int i,j;

					if(m_bMidButtonDown)
					{
						iMouseMotionX = e.button.x - m_sPreMousePosX; iMouseMotionY = e.button.y - m_sPreMousePosY;
						m_sPreMousePosX = e.button.x; m_sPreMousePosY = e.button.y; //先处理跟操作系统相关的变量

						glm::vec3 lpCamCtrlPots[4]; glm::vec3 vInitCamForward, vInitCamUp; //处理数学变换相关
						curCamera.GetCameraLocation(lpCamCtrlPots[0], vInitCamForward, vInitCamUp);
						lpCamCtrlPots[1] =lpCamCtrlPots[0]+glm::normalize(glm::cross(vInitCamForward, vInitCamUp));
						lpCamCtrlPots[2] =lpCamCtrlPots[0]+vInitCamForward;
						lpCamCtrlPots[3] =lpCamCtrlPots[0]+vInitCamUp;
						glm::vec3 vModelCenter =(bbModel.minPos+bbModel.maxPos)/2.0f;
						for(i =0; i<2; i++){
							glm::vec3 vCurRotAxis =glm::normalize((i == 0) ? lpCamCtrlPots[3]-lpCamCtrlPots[0] : lpCamCtrlPots[1]-lpCamCtrlPots[0]); //相机的转动轴
							float fCurRotAngle =((i == 0) ? (-float (iMouseMotionX) * 0.01f) : (-float (iMouseMotionY) * 0.01f));
							glm::mat4 matRotate =glm::translate(vModelCenter) * glm::rotate(fCurRotAngle, vCurRotAxis) * glm::translate(-vModelCenter);
							for(j =0; j<4; j++){
								glm::vec4 vTemp =matRotate*glm::vec4(lpCamCtrlPots[j].x, lpCamCtrlPots[j].y, lpCamCtrlPots[j].z, 1.0f); 
								lpCamCtrlPots[j] =glm::vec3(vTemp.x/vTemp.w, vTemp.y/vTemp.w, vTemp.z/vTemp.w);
							}
						}
						curCamera.SetCameraLocation(lpCamCtrlPots[0], lpCamCtrlPots[2]-lpCamCtrlPots[0], lpCamCtrlPots[3]-lpCamCtrlPots[0]);
					}else if(m_bLeftButtonDown)
					{
						iMouseMotionX = e.button.x - m_sPreMousePosX; iMouseMotionY = e.button.y - m_sPreMousePosY;
						m_sPreMousePosX = e.button.x; m_sPreMousePosY = e.button.y; //先处理跟操作系统相关的变量

						glm::vec3 vInitCamPos, vInitCamForword, vInitCamUp; float fCamFov, fCamZnear, fCamAspect; //先声明需要的局部变量
						curCamera.GetCameraLocation(vInitCamPos, vInitCamForword, vInitCamUp, fCamFov, fCamZnear, fCamAspect); //依次给局部变量赋值
						glm::vec3 vModelCenter =(bbModel.minPos+bbModel.maxPos)/2.0f;

						float fViewportY = 2.0f*tan(fCamFov/2)*fCamZnear; //先计算视口在世界空间下的实际长度
						float fViewportX = fViewportY*fCamAspect;

						float fCamMoveX = (float(iMouseMotionX)/WIDTH)*fViewportX*(::abs(glm::dot(vModelCenter-vInitCamPos,glm::normalize(vInitCamForword))))/fCamZnear; //根据三角关系将鼠标移动的像素数转换为物体在世界坐标系下移动的距离
						float fCamMoveY = (float(iMouseMotionY)/HEIGHT)*fViewportY*(::abs(glm::dot(vModelCenter-vInitCamPos,glm::normalize(vInitCamForword))))/fCamZnear;

						vInitCamPos -= fCamMoveX*glm::normalize(glm::cross(vInitCamForword, vInitCamUp)); //物体在世界坐标系下移动的距离转变为相机移动的反方向距离
						vInitCamPos += fCamMoveY*vInitCamUp;

						curCamera.SetCameraLocation(vInitCamPos, vInitCamForword, vInitCamUp);
					}else{
						m_sPreMousePosX = 0x7fffffff;
						m_sPreMousePosY = 0x7fffffff;
					}
				}
		}	
	}


#if 0
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT) //关闭SDL窗口的时候
		{		
			m_isClosed = true;
		}else if(e.type == SDL_MOUSEMOTION)
		{

		}else if(e.type == SDL_MOUSEBUTTONDOWN)
		{

		}else if(e.type == SDL_MOUSEBUTTONUP)
		{

		}else if(e.type == SDL_MOUSEWHEEL)
		{
			glm::vec3 curPos; glm::vec3 curFoword; glm::vec3 curUp;
			curCamera.GetCameraLocation(curPos, curFoword, curUp);
			glm::vec3 vModelCenter =(bbModel.minPos+bbModel.maxPos)/2.0f;
			float fDist =glm::length(curPos-vModelCenter); float fWalkLen =fDist*0.05f;
			glm::vec3 vDir =glm::normalize(vModelCenter-curPos);
			if(e.wheel.y == 1)
			{
				curPos +=vDir*fWalkLen;
			}else if(e.wheel.y == -1)
			{
				curPos -=vDir*fWalkLen;
			}
			curCamera.SetCameraLocation(curPos, curFoword, curUp);
		}
	}
#endif

}

bool Display::IsClosed()
{
	return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//窗口赋颜色初值
}