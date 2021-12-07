#include "pch.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitializeMatrix();
}

void Draw()
{
	ClearBackground(0.f, 0.f, 0.f);

	// Put your own draw statements here
	SetColor(1.f, 0.f, 0.f);
	DrawGrid();
}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void End()
{
	// free game resources here
	delete g_Matrix.pMatrix;
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void InitializeMatrix()
{
	//----------------------------initializing matrix parameters-------------------------------------
	/*	- cellPixelSize = The amount of pixels that defines the size of a grid cell.
		- sizeX			= Amount of cells on the horizontal plane.
		- sizeY			= Amount of cells on the vertical plane.
		- arraySize		= Size of the array that defines the matrix.
	*/
	g_CellPixelSize = gcd(int(g_WindowWidth), int(g_WindowHeight)) / g_GridScaler;
	const int	sizeX{ int(g_WindowWidth) / g_CellPixelSize }, 
				sizeY{ int(g_WindowHeight) / g_CellPixelSize },
				arraySize{ int(sizeX * sizeY) };

	std::cout << "Built matrix with dimensions " << sizeX << "x" << sizeY << " .\n";

	MatrixElement* pMatrix = new MatrixElement[arraySize];

	//--------------------------------Initializing matrix cells---------------------------------------
	for (int i{}; i < arraySize; i++)
	{
		const int x{ i % sizeX }, y{ i /  sizeX};
		const Point2f pointToAdd{ float(x * g_CellPixelSize), g_WindowHeight - float(y * g_CellPixelSize) };
		pMatrix[i].bottomLeft = pointToAdd;
	}

	g_Matrix.sizeX = sizeX;
	g_Matrix.sizeY = sizeY;
	g_Matrix.pMatrix = pMatrix;
}

void DrawGrid()
{
	const int	maxSize{ g_Matrix.sizeX * g_Matrix.sizeY };
	const float lineWidth{ 1.5f };
	
	for (int i{}; i < maxSize; i++ )
	{
		const int x{ i % g_Matrix.sizeX }, y{ i / g_Matrix.sizeX };
		Point2f origin{ g_Matrix.GetElement(x, y).bottomLeft };
		
		if (y != 0)
		{	
			if (x != 0)
			{
				// left
				Point2f left{ g_Matrix.GetElement(x - 1, y).bottomLeft };
				DrawLine(origin, left, lineWidth);
			}
			if (x == g_Matrix.sizeX - 1)
			{
				DrawRect(origin, float(g_CellPixelSize), float(g_CellPixelSize), lineWidth);
			}
			if (y == g_Matrix.sizeY - 1)
			{
				DrawRect(origin.x, origin.y - g_CellPixelSize, float(g_CellPixelSize), float(g_CellPixelSize), lineWidth);
			}

			//top
			Point2f top{ g_Matrix.GetElement(x, y - 1).bottomLeft };
			DrawLine(origin, top, lineWidth);
		}
		else if (x != 0)
		{
			// left
			Point2f left{ g_Matrix.GetElement(x - 1, y).bottomLeft };
			DrawLine(origin, left, lineWidth);
		}
	}
}
#pragma endregion ownDefinitions