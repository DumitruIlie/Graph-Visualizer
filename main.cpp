// Ilie Dumitru
#include<graphics.h>
#include"Graph.h"

bool isKeyPressed(int key)
{
	return GetKeyState(key) & 0x80000;
}

const int WindowWidth = GetSystemMetrics(SM_CXSCREEN), WindowHeight = GetSystemMetrics(SM_CYSCREEN);

int main()
{
	int window = initwindow(WindowWidth, WindowHeight, "Graph Visualiser", -3, -26, true);
	bool appRunning = true;
	Graph G;
	vec2i prevMouse, currMouse;

	if(!G.loadFromFile("graph.in"))
	{
		closegraph(window);
		return 0;
	}

	G.initPositions(vec2i(WindowWidth / 2, WindowHeight / 2), 100, true);
	currMouse.x = mousex();
	currMouse.y = mousey();

	do
	{
		appRunning ^= isKeyPressed(VK_ESCAPE);

		setbkcolor(WHITE);
		cleardevice();

		prevMouse = currMouse;
		currMouse.x = mousex();
		currMouse.y = mousey();

		G.processMouseInput(prevMouse, currMouse, isKeyPressed(VK_LBUTTON));

		if(!G.render(window, currMouse))
			appRunning = false;

		swapbuffers();
	}while(appRunning);

	closegraph(window);
	return 0;
}