#include "pch.h"
#include "Game.h"
#include <algorithm>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitializeMatrix();
	InitializePlayer();
	InitializeEnemy();
	InitializeGrid();
	InitializeGun();
	InitializeBullet();
	InitializeBackgroundMusic();
	InitializeTimer();
	InitializeTrap();
	InitializeEndScreenText();
}

void Draw()
{
	ClearBackground(0.f, 0.f, 0.f);

	// Put your own draw statements here
	SetColor(1.f, 0.f, 0.f);
	DrawGrid();
	DrawTextures();
	DrawTimer();
	DrawEndScreen();
}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	g_NrFrames++;
	UpdateTimer(elapsedSec);
	UpdateSpeed();


	if (!(g_NrFrames % g_DevisorSpeedE) && g_pEnemy != nullptr)
	{
		const Uint8* pStatesE = SDL_GetKeyboardState(nullptr);

		if (pStatesE[SDL_SCANCODE_RIGHT])
		{
			//std::cout << "\'rightarrow\' key is down\n";
			if (g_pEnemy->m_dir == DirectionState::right)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pEnemy->m_GridPos.x, g_pEnemy->m_GridPos.y);
				bool moved = g_pMatrix->MoveE(*g_pEnemy, *n);
				delete n;
				n = nullptr;
				KillEnemy(moved);
			}
			else
			{
				g_pEnemy->m_dir = DirectionState::right;
			}
		}
		if (pStatesE[SDL_SCANCODE_LEFT])
		{
			//std::cout << "\'leftarrow\' keys is down\n";
			if (g_pEnemy->m_dir == DirectionState::left)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pEnemy->m_GridPos.x, g_pEnemy->m_GridPos.y);
				bool moved = g_pMatrix->MoveE(*g_pEnemy, *n);
				delete n;
				n = nullptr;
				KillEnemy(moved);
			}
			else
			{
				g_pEnemy->m_dir = DirectionState::left;
			}
		}
		if (pStatesE[SDL_SCANCODE_UP])
		{
			//std::cout << "\'uparrow\' keys is down\n";
			if (g_pEnemy->m_dir == DirectionState::up)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pEnemy->m_GridPos.x, g_pEnemy->m_GridPos.y);
				bool moved = g_pMatrix->MoveE(*g_pEnemy, *n);
				delete n;
				n = nullptr;
				KillEnemy(moved);
			}
			else
			{
				g_pEnemy->m_dir = DirectionState::up;
			}
		}
		if (pStatesE[SDL_SCANCODE_DOWN])
		{
			//std::cout << "\'downarrow\' keys is down\n";
			if (g_pEnemy->m_dir == DirectionState::down)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pEnemy->m_GridPos.x, g_pEnemy->m_GridPos.y);
				bool moved = g_pMatrix->MoveE(*g_pEnemy, *n);
				delete n;
				n = nullptr;

				KillEnemy(moved);
			}
			else
			{
				g_pEnemy->m_dir = DirectionState::down;
			}
		}
	}
	//Neighbours* n = g_pMatrix->GetNeighbours(g_pEnemy->m_GridPos.x, g_pEnemy->m_GridPos.y);


	/*AStar();

	GridPosition move = FindMoveEnemy(g_pPlayer->m_GridPos);

	g_pEnemy->m_dir = FindMoveDir(g_pEnemy->m_GridPos, move);*/

	//bool moved = g_pMatrix->MoveE(*g_pEnemy, *n);
	//delete n;
	//n = nullptr;

	//if (!moved)
	//{
	//	if (g_pEnemy->dead)
	//	{
	//		// Delete enemies here.
	//		delete g_pEnemy;
	//		g_pEnemy = nullptr;
	//	}
	//}
	//else
	//{
	//	UpdateNodes();
	//}
if (!(g_NrFrames % g_DevisorSpeedP) && g_pPlayer != nullptr)
{
		const Uint8* pStatesP = SDL_GetKeyboardState(nullptr);
		if (pStatesP[SDL_SCANCODE_D])
		{
			//std::cout << "\'d\' key is down\n";
			if (g_pPlayer->m_dir == DirectionState::right)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pPlayer->m_GridPos.x, g_pPlayer->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_pPlayer, *n);
				/*if (!g_WasBeartTrapPlacedByPlayer)
				{
					g_pMatrix->MoveB(*g_pBullet, *n);
				}*/
				delete n;
				n = nullptr;
				KillPlayer(moved);
			}
			else
			{
				g_pPlayer->m_dir = DirectionState::right;
			}
		}
		if (pStatesP[SDL_SCANCODE_A])
		{
			//std::cout << "\'a\' keys is down\n";
			if (g_pPlayer->m_dir == DirectionState::left)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pPlayer->m_GridPos.x, g_pPlayer->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_pPlayer, *n);
				/*if (!g_WasBeartTrapPlacedByPlayer)
				{
					g_pMatrix->MoveB(*g_pBullet, *n);
				}*/
				delete n;
				n = nullptr;
				KillPlayer(moved);
			}
			else
			{
				g_pPlayer->m_dir = DirectionState::left;
			}
		}
		if (pStatesP[SDL_SCANCODE_W])
		{
			//std::cout << "\'w\' keys is down\n";
			if (g_pPlayer->m_dir == DirectionState::up)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pPlayer->m_GridPos.x, g_pPlayer->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_pPlayer, *n);
				/*if (!g_WasBeartTrapPlacedByPlayer)
				{
					g_pMatrix->MoveB(*g_pBullet, *n);
				}*/
				delete n;
				n = nullptr;
				KillPlayer(moved);
			}
			else
			{
				g_pPlayer->m_dir = DirectionState::up;
			}
		}
		if (pStatesP[SDL_SCANCODE_S])
		{
			//std::cout << "\'s\' keys is down\n";
			if (g_pPlayer->m_dir == DirectionState::down)
			{
				Neighbours* n = g_pMatrix->GetNeighbours(g_pPlayer->m_GridPos.x, g_pPlayer->m_GridPos.y);
				bool moved = g_pMatrix->MoveP(*g_pPlayer, *n);
				/*if (!g_WasBeartTrapPlacedByPlayer)
				{
					g_pMatrix->MoveB(*g_pBullet, *n);
				}*/
				delete n;
				n = nullptr;
				KillPlayer(moved);
			}
			else
			{
				g_pPlayer->m_dir = DirectionState::down;
			}
		}
	}
}

void End()
{
	// free game resources here
	delete g_pMatrix;
	g_pMatrix = nullptr;
	delete g_pBullet;
	g_pBullet = nullptr;
	delete g_pNodeMap;
	g_pNodeMap = nullptr;
	delete g_pCurrentNode;
	g_pCurrentNode = nullptr;
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_SPACE:
		g_WasBeartTrapPlacedByPlayer = true;
		break;
	}
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
	Node* pMapArray = new Node[arraySize];
	MatrixChar mapArray{ sizeX, sizeY,
		new char[arraySize]{	'i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i',
							'i','z','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','i','p','i','p','p','p','p','p','p','i',
							'i','p','p','p','p','p','i','p','p','p','p','p','p','i','p','i','i','p','p','p','p','p','i','p','p','p','p','p','p','p','p','i',
							'i','p','p','i','p','p','i','p','p','p','p','p','p','i','p','i','i','p','p','p','i','p','p','p','i','p','p','p','i','p','p','i',
							'i','p','p','i','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','i','p','i','p','p','p','i','p','p','i',
							'i','p','p','i','p','p','i','p','p','p','p','p','p','p','p','p','p','p','i','i','i','i','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','i','i','p','i','p','p','i','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','i','i','p','i','i',
							'i','p','i','i','p','p','i','p','p','i','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','p','p','p','i','p','i','i','i','p','p','i','i','i','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','i','p','i','p','p','i','p','p','i','p','p','p','i','p','p','p','p','i','p','p','i','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','i','p','p','i','p','p','i','p','p','p','i','p','p','p','p','i','p','p','i','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','i','p','p','i','p','p','p','p','p','p','i','p','p','i','i','i','p','i','i','i','p','p','i','i','p','i','i','p','i',
							'i','p','p','i','p','p','i','p','p','p','i','i','i','i','p','p','p','p','p','p','p','i','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','i','p','i','p','p','p','p','p','p','p','i','p','p','p','p','i','p','p','i','p','p','p','i','p','p','i','p','p','i',
							'i','p','p','p','p','i','p','p','p','i','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','p','i',
							'i','p','p','p','p','i','p','p','p','i','p','p','p','i','p','p','p','p','i','p','p','p','p','p','p','i','p','p','p','p','c','i',
							'i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i','i'} };

	//'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i',
	//	'i', 'z', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'i', 'i', 'i', 'p', 'p', 'i', 'i', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'i', 'p', 'p', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'i', 'i', 'i', 'p', 'p', 'i', 'i', 'i', 'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'i', 'i', 'i',
	//	'i', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'c', 'i',
	//	'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i',

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
		pArray[i].m_GridPos = gridPos;

		/*
		Building the map using the mapArray and applying it's defined states 
		to the world matrix according to the legend(line:112).
		*/
		bool obstacle{ false };
		if (mapArray.m_pMatrix[i] == 'i')
		{
			pArray[i].m_WorldState = WorldState::impassable;
			obstacle = true;
		}
		else if (mapArray.m_pMatrix[i] == 'p')
		{
			pArray[i].m_WorldState = WorldState::passable;
		}
		else if (mapArray.m_pMatrix[i] == 'z')
		{
			pArray[i].m_WorldState = WorldState::zombie;
			g_pEnemy = new Enemy{ gridPos, DirectionState::down};
			//TEMP:
			obstacle = true;
		}
		else if (mapArray.m_pMatrix[i] == 'c')
		{
			pArray[i].m_WorldState = WorldState::player;
			g_pPlayer = new Player{ gridPos, DirectionState::down };
		}
		else if (mapArray.m_pMatrix[i] == 'b')
		{
			pArray[i].m_WorldState = WorldState::danger;
			g_pBullet = new Bullet{ gridPos, DirectionState::down };
		}

		const Node nodeToAdd{obstacle, gridPos};
		pMapArray[i] = nodeToAdd;

	}
	//----------------------------------------------building the matrix-------------------------------------------------
	g_pNodeMap->m_SizeX = sizeX;
	g_pNodeMap->m_SizeY = sizeY;
	g_pNodeMap->m_pMap = pMapArray;

	g_pMatrix->m_SizeX = sizeX;
	g_pMatrix->m_SizeY = sizeY;
	g_pMatrix->m_pMatrix = pArray;
}

float Heuristic(GridPosition pos, GridPosition endPos)
{
	//return abs(pos.x - endPos.x) + abs(pos.y - endPos.y);
	return sqrt(powf(float(pos.x) - float(endPos.x), 2.f) + powf(float(pos.y) - float(endPos.y), 2.f));
}

bool AStar()
{
	//g_AStrIteration++;
	for (int i{}; i < g_pNodeMap->m_SizeX * g_pNodeMap->m_SizeY; i++)
	{
		g_pNodeMap->m_pMap[i].m_Visited = false;
		g_pNodeMap->m_pMap[i].m_GlobalGoal = 9999;
		g_pNodeMap->m_pMap[i].m_pParent = nullptr;
	}

	g_pCurrentNode = &g_pEnemy->m_GridPos;
	g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_GlobalGoal = Heuristic(*g_pCurrentNode, g_pPlayer->m_GridPos);
	g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_LocalGoal = 0; //TODO: either this doesn't work or for currentNode reassignment we get the wrong one.
	

	GridPosition* pNodeArray{ new GridPosition[g_pNodeMap->m_SizeX * g_pNodeMap->m_SizeY]{} };
	NodeList nodesToTest{ g_pNodeMap->m_SizeX * g_pNodeMap->m_SizeY, 0, pNodeArray};

	nodesToTest.AddOnIndex(0, *g_pCurrentNode);
	bool b1 = nodesToTest.m_NodeCount != 0;
	bool b2 = g_pCurrentNode->x != g_pPlayer->m_GridPos.x;
	bool b3 = g_pCurrentNode->y != g_pPlayer->m_GridPos.y;
	std::cout << "yes";

	while (nodesToTest.m_NodeCount != 0 
		|| (g_pCurrentNode->x != g_pPlayer->m_GridPos.x 
		&& g_pCurrentNode->y != g_pPlayer->m_GridPos.y))
	{
		GridPosition FirstNodeLocalGoal = g_pNodeMap->GetNodeOnGridPos(nodesToTest.m_pList[0])->m_GridPos;
		GridPosition CurrentNodeLocalGoal = g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_GridPos;
		std::cout << "yes";
		nodesToTest.Sort();
		

		while(nodesToTest.m_NodeCount != 0 
			&& g_pNodeMap->GetNodeOnGridPos(nodesToTest.m_pList[0])->m_Visited)
		{
			nodesToTest.PopOnIndex(0);
		}

		if (nodesToTest.m_NodeCount == 0) break;

		g_pCurrentNode = &nodesToTest.m_pList[0];
		g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_Visited = true;
		std::cout << "yes";

		NodeNeighbours* neighboursArray = g_pNodeMap->GetNeighbours(g_pCurrentNode->x, g_pCurrentNode->y);
		Node test0 = neighboursArray->m_pNodes[2];
		std::cout << "yes";
		//if (g_AStrIteration == 1)
		//{

		//	std::cout << "yes";
		//}
		for (int i{}; i < neighboursArray->m_Count; i++)
		{

			int FirstNodeLocalGoal = g_pNodeMap->GetNodeOnGridPos(nodesToTest.m_pList[0])->m_LocalGoal;
			int CurrentNodeLocalGoal = g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_LocalGoal;
			GridPosition test1 = neighboursArray->m_pNodes[i].m_GridPos;
			bool  test2 = g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_Obstacle;
			std::cout << "yes";
			if (!g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_Visited
				|| !g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_Obstacle)
			{
				nodesToTest.AddOnIndex(0, g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_GridPos);
			}

			int FirstNodeLocalGoal0 = g_pNodeMap->GetNodeOnGridPos(nodesToTest.m_pList[1])->m_LocalGoal;
			int CurrentNodeLocalGoal0 = g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_LocalGoal;
			int possiblylowerGoal = g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode)->m_LocalGoal + 1;
			int neighbourLocalGoal = g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_LocalGoal;
			std::cout << "no";
			if (possiblylowerGoal < g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_LocalGoal)
			{
				g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_pParent = g_pNodeMap->GetNodeOnGridPos(*g_pCurrentNode);

				g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_LocalGoal = possiblylowerGoal;
				
				g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_GlobalGoal =
					float(g_pNodeMap->GetNodeOnGridPos(neighboursArray->m_pNodes[i].m_GridPos)->m_LocalGoal)
					+ Heuristic(neighboursArray->m_pNodes->m_GridPos, g_pPlayer->m_GridPos);
			}
		}
	}
	return true;
}

GridPosition FindMoveEnemy(GridPosition currentPos)
{
	if (g_pNodeMap->GetNodeOnGridPos(currentPos)->m_pParent != nullptr)
	{
		if (g_pNodeMap->GetNodeOnGridPos(currentPos)->m_pParent->m_pParent == nullptr)
		{
			return currentPos;
		}
		return FindMoveEnemy(g_pNodeMap->GetNodeOnGridPos(currentPos)->m_pParent->m_GridPos);
	}
	std::cerr << "Error\t-->\tshortest path is to short for determining next move";
	return GridPosition{};

}

DirectionState FindMoveDir(GridPosition enemy, GridPosition move)
{
	if (enemy.x < move.x)
	{
		return DirectionState::right;
	}
	else if (enemy.x > move.x)
	{
		return DirectionState::left;
	}
	else if (enemy.y < move.y)
	{
		return DirectionState::down;
	}
	else
	{
		return DirectionState::up;
	}
}

//TODO: check what happens if it is only generated for passable
//TODO: Remove temp variable and use Getter functions.
void UpdateNodes()
{
	const int    arraySize{ g_pMatrix->m_SizeX * g_pMatrix->m_SizeY };
	for (int i{}; i < arraySize; i++)
	{
		const int x{ i % g_pMatrix->m_SizeX }, y{ i / g_pMatrix->m_SizeX };
		Point2f origin{ g_pMatrix->GetElement(x, y).m_Position };

		Node temp{ g_pNodeMap->GetNode(x, y) };

		switch (g_pMatrix->GetElement(x, y).m_WorldState)
		{
		case WorldState::passable:
			
			temp.m_Obstacle = false;
			g_pNodeMap->m_pMap[y * g_pNodeMap->m_SizeX + x] = temp;
			break;
		case WorldState::impassable:
			temp.m_Obstacle = true;
			g_pNodeMap->m_pMap[y * g_pNodeMap->m_SizeX + x] = temp;
			break;
		case WorldState::danger:
			temp.m_Obstacle = false;
			g_pNodeMap->m_pMap[y * g_pNodeMap->m_SizeX + x] = temp;
			break;
		case WorldState::player:
			temp.m_Obstacle = false;
			g_pNodeMap->m_pMap[y * g_pNodeMap->m_SizeX + x] = temp;
			break;
		}
	}
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

		//DrawRect(origin, float(g_CellPixelSize), float(g_CellPixelSize), lineWidth);
		DrawTexture(g_Passable, origin);
		switch (g_pMatrix->GetElement(x, y).m_WorldState)
		{
		case WorldState::impassable:
			//HatchSquare(g_pMatrix->GetElement(x, y).m_Position, float(g_CellPixelSize), 15);
			DrawTexture(g_Unpassable, origin);
			break;
		default:
			break;
		}
	}
}

void DrawTextures()
{
	/*
	- arraySize	= The size of the array that represents the matrix.
*/
	const int	arraySize{ g_pMatrix->m_SizeX * g_pMatrix->m_SizeY };

	for (int i{}; i < arraySize; i++)
	{
		const int x{ i % g_pMatrix->m_SizeX }, y{ i / g_pMatrix->m_SizeX };
		Point2f origin{ g_pMatrix->GetElement(x, y).m_Position };
		Point2f weaponPos{ origin };
		int weaponOffset{ 21 };
		Point2f enemyPos{ origin };
		int enemyOffset{ 13 };

		switch (g_pMatrix->GetElement(x, y).m_WorldState)
		{
		case WorldState::passable:
			break;
		case WorldState::impassable:

			break;
		case WorldState::breakable:

			break;
		case WorldState::danger:
			if (g_WasBeartTrapPlacedByPlayer)
			{
				DrawTexture(g_TrapTexture, origin);
			}
			break;
		case WorldState::player:
			if (g_pPlayer->m_dir == DirectionState::left)
			{
				weaponPos.x -= weaponOffset;
				DrawTexture(g_pGunTextures[int(g_pPlayer->m_dir)], weaponPos);
			}
			else if (g_pPlayer->m_dir == DirectionState::down)
			{
				weaponPos.y -= weaponOffset;
				DrawTexture(g_pGunTextures[int(g_pPlayer->m_dir)], weaponPos);
			}
			else
			{
				DrawTexture(g_pGunTextures[int(g_pPlayer->m_dir)], origin);
			}
			DrawTexture(g_pPlayerTexture[int(g_pPlayer->m_dir)], origin);
			break;
		case WorldState::zombie:
			if (g_pEnemy->m_dir == DirectionState::left)
			{
				enemyPos.x -= enemyOffset;
				DrawTexture(g_pEnemyTexture[int(g_pEnemy->m_dir)], enemyPos);
			}
			else if (g_pEnemy->m_dir == DirectionState::down)
			{
				enemyPos.y -= enemyOffset;
				DrawTexture(g_pEnemyTexture[int(g_pEnemy->m_dir)], enemyPos);
			}
			else
			{
				DrawTexture(g_pEnemyTexture[int(g_pEnemy->m_dir)], origin);
			}
			//std::cout << origin.x << "     " << origin.y << '\n'; 120 560
			break;
		default:
			break;
		}
	}
}

void DrawTimer()
{
	Point2f pos{g_WindowWidth/ 2.f - (g_TimerText.width / 2.f), g_WindowHeight - (g_TimerText.height)};
	Rectf destinationRectangle{};
	destinationRectangle.bottom = pos.y;
	destinationRectangle.left = pos.x;
	destinationRectangle.width = g_TimerText.width;
	destinationRectangle.height = g_TimerText.height;
	//Rectf sourceRectangle{};
	//sourceRectangle.left = 0;
	//sourceRectangle.bottom = 0;
	//sourceRectangle.width = g_TimerText.width/2.f;
	//sourceRectangle.height = g_TimerText.height;
	//DrawTexture(g_TimerText, destinationRectangle);
}
//TODO: Somehow try to change the messy was of inicializing if possible
void InitializePlayer()
{
	bool iniSuccess[g_AmountOfText]{};
	iniSuccess[0] = TextureFromFile("Resources/Player/p_up.png", g_PlayerTextures[0]);
	iniSuccess[1] = TextureFromFile("Resources/Player/p_right.png", g_PlayerTextures[1]);
	iniSuccess[2] = TextureFromFile("Resources/Player/p_down.png", g_PlayerTextures[2]);
	iniSuccess[3] = TextureFromFile("Resources/Player/p_left.png", g_PlayerTextures[3]);
	
	for (int i{}; i < g_AmountOfText; i++)
	{
		if (!iniSuccess[i])
		{
			std::cout << "Texture for player failed to load INDEX: " << iniSuccess[i] << '\n';
		}
	}
	g_pPlayerTexture = g_PlayerTextures;
}

void InitializeEnemy()
{
	bool iniSuccess[g_AmountOfText]{};
	iniSuccess[0] = TextureFromFile("Resources/Enemy/z_up.png", g_EnemyTextures[0]);
	iniSuccess[1] = TextureFromFile("Resources/Enemy/z_right.png", g_EnemyTextures[1]);
	iniSuccess[2] = TextureFromFile("Resources/Enemy/z_down.png", g_EnemyTextures[2]);
	iniSuccess[3] = TextureFromFile("Resources/Enemy/z_left.png", g_EnemyTextures[3]);

	for (int i{}; i < g_AmountOfText; i++)
	{
		if (!iniSuccess[i])
		{
			std::cout << "Texture for enemy failed to load INDEX: " << iniSuccess[i] << '\n';
		}
		//std::cout << "[" << g_EnemyTextures[i].width << ", " << g_EnemyTextures[i].height << "]\n";
	}
	g_pEnemyTexture = g_EnemyTextures;
}

void InitializeGun()
{
	bool iniSuccess[g_AmountOfText]{};
	iniSuccess[0] = TextureFromFile("Resources/Weapons/p_up.png", g_GunTextures[0]);
	iniSuccess[1] = TextureFromFile("Resources/Weapons/p_right.png", g_GunTextures[1]);
	iniSuccess[2] = TextureFromFile("Resources/Weapons/p_down.png", g_GunTextures[2]);
	iniSuccess[3] = TextureFromFile("Resources/Weapons/p_left.png", g_GunTextures[3]);

	for (int i{}; i < g_AmountOfText; i++)
	{
		if (!iniSuccess[i])
		{
			std::cout << "Texture for player failed to load INDEX: " << iniSuccess[i] << '\n';
		}
	}
	g_pGunTextures = g_GunTextures;
}

void InitializeGrid()
{
	//changing the letter before _Pass.png and _Unpass.png to e, s, g changes the map
	bool iniSuccess{};
	iniSuccess = TextureFromFile("Resources/Environment/e_Pass.png", g_Passable);
	if (!iniSuccess)
	{
		std::cout << "Texture for passable failed to load\n";
	}
	iniSuccess = TextureFromFile("Resources/Environment/e_Unpass.png", g_Unpassable);
	if (!iniSuccess)
	{
		std::cout << "Texture for unpassable failed to load\n";
	}
}
void InitializeBullet()
{
	//bool iniSuccess[g_AmountOfText]{};
	//iniSuccess[0] = TextureFromFile("Resources/Bullet/b_up.png", g_TrapTexture[0]);
	//iniSuccess[1] = TextureFromFile("Resources/Bullet/b_right.png", g_TrapTexture[1]);
	//iniSuccess[2] = TextureFromFile("Resources/Bullet/b_down.png", g_TrapTexture[2]);
	//iniSuccess[3] = TextureFromFile("Resources/Bullet/b_left.png", g_TrapTexture[3]);

	//for (int i{}; i < g_AmountOfText; i++)
	//{
	//	if (!iniSuccess[i])
	//	{
	//		std::cout << "Texture for bullet failed to load INDEX: " << iniSuccess[i] << '\n';
	//	}
	//}
	//g_pBulletTextures = g_TrapTexture;
}
void InitializeTrap()
{
	if(!TextureFromFile("Resources/Interactables/beartrap.png", g_TrapTexture)) std::cout << "Texture for Trap failed to load: \n";
}

void InitializeBackgroundMusic()
{
	//you can switch songs by chaanging the digit from 1- 4
	const char* song{ "Resources/Sounds/bc_music3.mp3" };

	int audioHertz{ 22050 }; //default is 22050
	Uint16 audioFormat{ AUDIO_S16SYS };
	int audioChannel{ 2 };
	int audioBuffer{ 4096 };
	if (Mix_OpenAudio(audioHertz, audioFormat, audioChannel, audioBuffer) != 0)
	{
		std::cout << "Rip audio\n";
	}
	//Mix_Volume(0, MIX_MAX_VOLUME);
	Mix_PlayChannel(-1, Mix_LoadWAV(song), 0);
}

void KillEnemy(bool moved)
{
	if (!moved)
	{
		if (g_pEnemy->dead)
		{
			// Delete player here.
			delete g_pEnemy;
			g_pEnemy = nullptr;
			g_DidZombieCaughtUpToThePlayer = true;
		}
	}
}

void KillPlayer(bool moved)
{
	if (!moved)
	{
		if (g_pPlayer->dead)
		{
			// Delete player here.
			delete g_pPlayer;
			g_pPlayer = nullptr;
			g_DidZombieCaughtUpToThePlayer = true;
		}
	}
}
void InitializeTimer()
{
	if (!TextureFromString("Hi Boomer", "Resources/Fonts/RobotoMono-Medium.ttf", g_TimerFontSize, g_TimerColour, g_TimerText)) std::cout << "Image not found RobotoMono-Medium.ttf\n";
}

void UpdateTimer(float elapsedTime)
{
	int amountOfFrames{ 60 };
	if (g_Timer >= 0)
	{
		if (g_NrFrames % amountOfFrames == 0)
		{
			std::cout << "Time left: " << g_Timer << '\n';
			g_Timer--;
		}
	}
	else
	{
		g_DidTheTimeRunOut = true;
	}
}

void InitializeEndScreenText()
{
	if (!TextureFromString("Player survived and won!", "Resources/Fonts/RobotoMono-Medium.ttf", g_EndScreenFontSizeForText, g_EndScreenFontColurForText, g_EndScreenWinText)) std::cout << "Image not found RobotoMono-Medium.ttf\n";
	if (!TextureFromString("Zombie has eaten your brain!", "Resources/Fonts/RobotoMono-Medium.ttf", g_EndScreenFontSizeForText, g_EndScreenFontColurForText, g_EndScreenLooseText)) std::cout << "Image not found RobotoMono-Medium.ttf\n";
}

void DrawEndScreen()
{
	Point2f pos1{ g_WindowWidth / 2.f - (g_EndScreenLooseText.width / 2.f) , g_WindowHeight / 2.f};
	Point2f pos2{ g_WindowWidth / 2.f - (g_EndScreenWinText.width / 2.f) , g_WindowHeight / 2.f };

	if (g_DidZombieCaughtUpToThePlayer)
	{
		SetColor(0,0,0,1);
		FillRect(0, 0, g_WindowWidth, g_WindowHeight);
		DrawTexture(g_EndScreenLooseText, pos1);

	}
	else if (g_DidTheTimeRunOut)
	{
		SetColor(0, 0, 0, 1);
		FillRect(0, 0, g_WindowWidth, g_WindowHeight);
		DrawTexture(g_EndScreenWinText, pos2);
	}
}
void UpdateSpeed()
{
	int bonusSpeed{g_DevisorSpeedP / 10};
	if (g_Timer < (g_MaxTime * 3 / 4) 
		&& g_Timer > (g_MaxTime / 2)
		&& g_SpeedChecker[0] == false)
	{
		g_DevisorSpeedE -= bonusSpeed;
		//std::cout << g_DevisorSpeedE;
		g_SpeedChecker[0] = true;
	}
	else if (g_Timer < (g_MaxTime / 2) 
		&& g_Timer > (g_MaxTime / 3)
		&& g_SpeedChecker[1] == false)
	{
		g_DevisorSpeedE -= bonusSpeed;
		//std::cout << g_DevisorSpeedE;
		g_SpeedChecker[1] = true;
	}
	else if (g_Timer < (g_MaxTime / 3) 
		&& g_Timer >(g_MaxTime / 4)
		&& g_SpeedChecker[2] == false)
	{
		g_DevisorSpeedE -= bonusSpeed;
		//std::cout << g_DevisorSpeedE;
		g_SpeedChecker[2] = true;
	}
	else if (g_Timer < (g_MaxTime / 4) 
		&& g_SpeedChecker[3] == false)
	{
		g_DevisorSpeedE -= bonusSpeed;
		//std::cout << g_DevisorSpeedE;
		g_SpeedChecker[3] = true;
	}
}
#pragma endregion ownDefinitions