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
	//InitializePlayer();
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
	g_NrFrames++;
	if (!(g_NrFrames % 30) && g_Player != nullptr)
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_D])
		{
			std::cout << "\'d\' key is down\n";
			if (g_Player->m_dir == DirectionState::right)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_Player->m_GridPos.x, g_Player->m_GridPos.y);
				 bool moved = g_pMatrix->MoveP(*g_Player, *n);
				delete n;

				if (!moved)
				{
					if (g_Player->dead)
					{
						// Delete player here.
						delete g_Player;
						g_Player = nullptr;
					}
				}
			}
			else
			{
				g_Player->m_dir = DirectionState::right;
			}
		}
		if (pStates[SDL_SCANCODE_A])
		{
			std::cout << "\'a\' keys is down\n";
			if (g_Player->m_dir == DirectionState::left)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_Player->m_GridPos.x, g_Player->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_Player, *n);
				delete n;

				if (!moved)
				{
					if (g_Player->dead)
					{
						// Delete player here.
						delete g_Player;
						g_Player = nullptr;
					}
				}
			}
			else
			{
				g_Player->m_dir = DirectionState::left;
			}
		}
		if (pStates[SDL_SCANCODE_W])
		{
			std::cout << "\'w\' keys is down\n";
			if (g_Player->m_dir == DirectionState::up)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_Player->m_GridPos.x, g_Player->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_Player, *n);
				delete n;

				if (!moved)
				{
					if (g_Player->dead)
					{
						// Delete player here.
						delete g_Player;
						g_Player = nullptr;
					}
				}
			}
			else
			{
				g_Player->m_dir = DirectionState::up;
			}
		}
		if (pStates[SDL_SCANCODE_S])
		{
			std::cout << "\'s\' keys is down\n";
			if (g_Player->m_dir == DirectionState::down)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_Player->m_GridPos.x, g_Player->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_Player, *n);
				delete n;

				if (!moved)
				{
					if (g_Player->dead)
					{
						// Delete player here.
						delete g_Player;
						g_Player = nullptr;
					}
				}
			}
			else
			{
				g_Player->m_dir = DirectionState::down;
			}
		}

		if (g_Enemy != nullptr)
		{
			Neighbours* n = g_pMatrix->GetNeighbours(g_Enemy->m_GridPos.x, g_Enemy->m_GridPos.y);
			bool moved = g_pMatrix->MoveE(*g_Enemy, *n);
			delete n;

			if (!moved)
			{
				if (g_Enemy->dead)
				{
					// Delete enemies here.
					delete g_Enemy;
					g_Enemy = nullptr;
				}
			}
		}
	}
}

void End()
{
	// free game resources here
	delete g_pMatrix;
	delete g_Bullet;
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
	//---------------------------------------initializing matrix parameters--------------------------------------------
	/*	- cellPixelSize = The amount of pixels that defines the size of a grid cell.
		- sizeX			= Amount of cells on the horizontal plane.
		- sizeY			= Amount of cells on the vertical plane.
		- arraySize		= Size of the array that defines the matrix.
		- pArray		= Pointer to the array used as a matrix to represent our game world.
		- mapArray		= Character array where we make the map to apply on our world matrix.
						  Legend:
									- i = impassible terrain.
									- p = passable terrain.
									- d = dangerous terrain, for example a bullet or a grid cell near an enemy.
									- b = breakable terrain, a placable barrel/wall object.
									- z = zombie.
									- c = player character.
	*/
	g_CellPixelSize = gcd(int(g_WindowWidth), int(g_WindowHeight)) / g_GridScaler;
	const int	sizeX{ int(g_WindowWidth) / g_CellPixelSize }, 
				sizeY{ int(g_WindowHeight) / g_CellPixelSize },
				arraySize{ int(sizeX * sizeY) };

	std::cout << "Built matrix with dimensions " << sizeX << "x" << sizeY 
		<< " .\nPixel count per grid cell is " << g_CellPixelSize << "\n";

	MatrixElement* pArray = new MatrixElement[arraySize];
	MatrixChar mapArray{ sizeX, sizeY,
		new char[arraySize]{'i','p','p','p','p','p','i','i','i','i','i','i','i','i','p','p','p','p','i','i','i','i','i','i','i','i','i','i','i','i','i','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i',
							'i','p','p','z','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','i','i','i','i','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','c','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','i','i','i','i','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','b','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','i','i','i','i','i','i','i','i','i','i','i','i','i','p','p','p','p','i','i','i','i','i','i','i','i','p','p','p','p','p','i'} };
	//------------------------------------------Initializing matrix cells----------------------------------------------
	for (int i{}; i < arraySize; i++)
	{
		/*
		Adding the points containing the pixel coordinates of the bottom left croner of the corresponding grid cells.
		*/
		const int x{ i % sizeX }, y{ i /  sizeX};
		const Point2f pointToAdd{ float(x * g_CellPixelSize), g_WindowHeight - float((y + 1) * g_CellPixelSize) };
		const GridPosition gridPos{ x, y };
		pArray[i].m_Position = pointToAdd;
		pArray[i].m_GridPosition = gridPos;

		/*
		Building the map using the mapArray and applying it's defined states 
		to the world matrix according to the legend(line:112).
		*/
		if (mapArray.m_pMatrix[i] == 'i')
		{
			pArray[i].m_WorldState = WorldState::impassable;
		}
		else if (mapArray.m_pMatrix[i] == 'p')
		{
			pArray[i].m_WorldState = WorldState::passable;
		}
		else if (mapArray.m_pMatrix[i] == 'z')
		{
			pArray[i].m_WorldState = WorldState::zombie;
			g_Enemy = new Enemy{ gridPos, DirectionState::down };
		}
		else if (mapArray.m_pMatrix[i] == 'c')
		{
			pArray[i].m_WorldState = WorldState::player;
			g_Player = new Player{ gridPos, DirectionState::down };
		}
		else if (mapArray.m_pMatrix[i] == 'b')
		{
			pArray[i].m_WorldState = WorldState::danger;
			g_Bullet = new Bullet{ gridPos, DirectionState::down };
		}
	}
	//----------------------------------------------building the matrix-------------------------------------------------

	g_pMatrix->m_SizeX = sizeX;
	g_pMatrix->m_SizeY = sizeY;
	g_pMatrix->m_pMatrix = pArray;
}

void DrawGrid()
{
	/*
		- arraySize	= The size of the array that represents the matrix.
		- lineWidth	= The pixel width of the lines.
	*/
	const int	arraySize{ g_pMatrix->m_SizeX * g_pMatrix->m_SizeY };
	const float lineWidth{ 2.f };

	for (int i{}; i < arraySize; i++)
	{
		const int x{ i % g_pMatrix->m_SizeX }, y{ i / g_pMatrix->m_SizeX };
		Point2f origin{ g_pMatrix->GetElement(x, y).m_Position };

		DrawRect(origin, float(g_CellPixelSize), float(g_CellPixelSize), lineWidth);
		
		switch (g_pMatrix->GetElement(x, y).m_WorldState)
		{
		case WorldState::impassable:
			HatchSquare(g_pMatrix->GetElement(x, y).m_Position, float(g_CellPixelSize), 15);
			break;
		case WorldState::passable:
			break;
		case WorldState::breakable:
			break;
		case WorldState::danger:
			SetColor(0.f, 0.5f, 0.5f);
			HatchSquare(g_pMatrix->GetElement(x, y).m_Position, float(g_CellPixelSize), 15);
			SetColor(1.f, 0.f, 0.f);
			break;
		case WorldState::player:
			SetColor(0.f, 0.f, 1.f);
			HatchSquare(g_pMatrix->GetElement(x, y).m_Position, float(g_CellPixelSize), 15);
			SetColor(1.f, 0.f, 0.f);
			break;
		case WorldState::zombie:
			SetColor(0.f, 1.f, 0.f);
			HatchSquare(g_pMatrix->GetElement(x, y).m_Position, float(g_CellPixelSize), 15);
			SetColor(1.f, 0.f, 0.f);
			break;
		default:
			break;
		}
	}
}

void InitializePlayer()
{
	bool wasInicializationSuccess{};
}

#pragma endregion ownDefinitions