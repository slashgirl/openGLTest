#ifndef _DISPLAY_H
#define  _DISPLAY_H

//´´½¨´°¿Ú

#include <string>
#include "sdl2/SDL.h"
#include "GL/glew.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Update();
	bool IsClosed();
	void Clear(float r, float g, float b, float a);

	~Display();
protected:
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};






#endif
