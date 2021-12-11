#include "pch.h"
#include "structs.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window( const std::string& title , float width , float height , bool isVSyncOn )
	:title{ title }
	,width{ width }
	,height{ height }
	,isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f( )
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f( float x, float y )
	:x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf( )
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf( float left, float bottom, float width, float height )
	:left{ left }
	,bottom{ bottom }
	,width{ width }
	,height{ height }
{
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f( )
	:Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f( float r, float g, float b, float a )
	:r{ r }
	,g{ g }
	,b{ b }
	,a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef( )
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef( float centerX, float centerY, float radius )
	:Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef( const Point2f& center, float radius )
	:center{ center }
	,radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef( )
	:Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}


Ellipsef::Ellipsef( const Point2f& center, float radiusX, float radiusY )
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

Ellipsef::Ellipsef( float centerX, float centerY, float radiusX, float radiusY )
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}


Vector2f::Vector2f() 
	:Vector2f{0.f, 0.f}
{
}

Vector2f::Vector2f(float x, float y)
	: x(x), y(y)
{
}

MatrixChar::MatrixChar(const int x, const int y, char* charArray)
	: m_SizeX(x), m_SizeY(y), m_pMatrix(charArray)
{
}

MatrixChar::~MatrixChar()
{
}

MatrixElement::MatrixElement()
	: MatrixElement{ WorldState::passable, Point2f{}, GridPosition{} }
{
}

MatrixElement::MatrixElement(WorldState worldState, Point2f bottomLeft, GridPosition gridPos)
	: m_WorldState(worldState), m_Position(bottomLeft), m_GridPos(gridPos)
{
}

MatrixElement::~MatrixElement()
{
}

Matrix::Matrix()
	: Matrix{ 1, 1, nullptr }
{
}

Matrix::Matrix(const int sizeX, const int sizeY, MatrixElement* pMatrix)
	: m_SizeX(sizeX), m_SizeY(sizeY), m_pMatrix(pMatrix)
{
}

Matrix::~Matrix()
{
	delete[] m_pMatrix;
	m_pMatrix = nullptr;
}

MatrixElement Matrix::GetElement(const int x, const int y)
{
	const int index{ int(m_SizeX) * y + x };
	return m_pMatrix[index];
}

Neighbours* Matrix::GetNeighbours(const int x, const int y)
{
	if (x == 0)
	{
		if (y == 0)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x + 1, y), 
														GetElement(x, y + 1)} };
		}
		else if (y == m_SizeY)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x + 1, y), 
														GetElement(x, y - 1) } };
		}
		else
		{
			return new Neighbours{ 2, new MatrixElement[3]{ GetElement(x, y - 1), 
														GetElement(x + 1, y), 
														GetElement(x, y + 1) } };
		}
	}
	else if (x == m_SizeX)
	{
		if (y == 0)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x - 1, y),
														GetElement(x, y + 1) } };
		}
		else if (y == m_SizeY)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x - 1, y),
														GetElement(x, y - 1) } };
		}
		else
		{
			return new Neighbours{ 2, new MatrixElement[3]{ GetElement(x, y - 1),
														GetElement(x, y + 1),
														GetElement(x - 1, y) } };
		}
	}
	else if (y == 0)
	{
		if (x == 0)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x + 1, y),
														GetElement(x, y + 1) } };
		}
		else if (x == m_SizeX)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x - 1, y),
														GetElement(x, y + 1) } };
		}
		else
		{
			;
			return new Neighbours{ 3,  new MatrixElement[3]{ GetElement(x + 1, y),
														GetElement(x, y + 1),
														GetElement(x - 1, y) }};
		}
	}
	else if (y == m_SizeY)
	{
		if (x == 0)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x + 1, y),
														GetElement(x, y - 1) } };
		}
		else if (x == m_SizeX)
		{
			return new Neighbours{ 2, new MatrixElement[2]{ GetElement(x - 1, y),
														GetElement(x, y - 1) } };
		}
		else
		{
			return new Neighbours{ 3, new MatrixElement[3]{ GetElement(x, y - 1),
														GetElement(x + 1, y),
														GetElement(x - 1, y) } };
		}
	}
	else
	{
		return new Neighbours{ 4, new MatrixElement[4]{ GetElement(x, y - 1),
													GetElement(x + 1, y),
													GetElement(x, y + 1),
													GetElement(x - 1, y) } };
	}
}

void Matrix::UpdateCellState(const int x, const int y, WorldState state)
{
	m_pMatrix[y * m_SizeX + x].m_WorldState = state;
}

bool Matrix::MoveE(Enemy& enemy, const Neighbours& neighbours)
{
	switch (enemy.m_dir)
	{
	case DirectionState::up:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x == neighbours.m_pElements[i].m_GridPos.x) 
				&& (enemy.m_GridPos.y - 1 == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x, 
									neighbours.m_pElements[i].m_GridPos.y, WorldState::zombie);
					enemy.m_GridPos.y--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::right:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x + 1 == neighbours.m_pElements[i].m_GridPos.x)
				&& (enemy.m_GridPos.y == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::zombie);
					enemy.m_GridPos.x++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::down:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x == neighbours.m_pElements[i].m_GridPos.x)
				&& (enemy.m_GridPos.y + 1 == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::zombie);
					enemy.m_GridPos.y++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::left:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x - 1 == neighbours.m_pElements[i].m_GridPos.x)
				&& (enemy.m_GridPos.y == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::zombie);
					enemy.m_GridPos.x--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}

bool Matrix::MoveP(Player& player, const Neighbours& neighbours)
{
	switch (player.m_dir)
	{
	case DirectionState::up:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((player.m_GridPos.x == neighbours.m_pElements[i].m_GridPos.x)
				&& (player.m_GridPos.y - 1 == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::player);
					player.m_GridPos.y--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					player.dead = true;
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::right:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((player.m_GridPos.x + 1 == neighbours.m_pElements[i].m_GridPos.x)
				&& (player.m_GridPos.y == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::player);
					player.m_GridPos.x++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					player.dead = true;
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::down:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((player.m_GridPos.x == neighbours.m_pElements[i].m_GridPos.x)
				&& (player.m_GridPos.y + 1 == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::player);
					player.m_GridPos.y++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					player.dead = true;
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::left:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((player.m_GridPos.x - 1 == neighbours.m_pElements[i].m_GridPos.x)
				&& (player.m_GridPos.y == neighbours.m_pElements[i].m_GridPos.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPos.x,
						neighbours.m_pElements[i].m_GridPos.y, WorldState::player);
					player.m_GridPos.x--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					player.dead = true;
					UpdateCellState(player.m_GridPos.x, player.m_GridPos.y, WorldState::passable);
					return false;
				}
			}
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}

bool Matrix::MoveB(Bullet& bullet, const Neighbours& neighbours)
{
	return false;
}

Neighbours::Neighbours(const int arraySize, MatrixElement* elements)
	:m_Count(arraySize), m_pElements(elements)
{
}

Neighbours::~Neighbours()
{
	delete[] m_pElements;
	m_pElements = nullptr;
}

GridPosition::GridPosition():
	x(0), y(0)
{
}

GridPosition::GridPosition(const int x, const int y)
	:x(x), y(y)
{
}

GridPosition::~GridPosition()
{
}

Enemy::Enemy()
	:m_GridPos(GridPosition{}), m_dir(DirectionState::down)
{
}

Enemy::Enemy(GridPosition gridPos, DirectionState dir)
	:m_GridPos(gridPos), m_dir(dir)
{
}

Enemy::~Enemy()
{
}

Player::Player()
	:m_GridPos(GridPosition{}), m_dir(DirectionState::down)
{
}

Player::Player(GridPosition gridPos, DirectionState dir)
	: m_GridPos(gridPos), m_dir(dir)
{
}

Player::~Player()
{
}

Bullet::Bullet()
	:m_GridPos(GridPosition{}), m_dir(DirectionState{})
{
}

Bullet::Bullet(GridPosition gridPos, DirectionState dir)
	:m_GridPos(gridPos), m_dir(dir)
{
}

Bullet::~Bullet()
{
}

NodeList::NodeList()
	:m_Size(0), m_NodeCount(0), m_pList(nullptr)
{
}

NodeList::NodeList(const int size, const int nodeCount, GridPosition* pPosArray)
	:m_Size(size), m_NodeCount(nodeCount), m_pList(pPosArray)
{
}

NodeList::~NodeList()
{
}

/*	
	parameters:		- index1	= The index of the first element of the pair that needs to be swapped.
					- index2	= The index of the second element of the pair that needs to be swapped.
	definition:		The element of the list at index1 is swapped with the element of the list at index2.
*/
void NodeList::SwapElements(const int index1, const int index2)
{
}

/*	
	parameters:		- startIndex	= The index from which to start shifting elements to the right.
	requirements:	The list needs to be filled up from left to right (no empty indexes).
	definition:		The lists elements will each be shifted right one position starting from the last element
					up to the element at the startIndex.
*/
void NodeList::ShiftRightFromIndex(const int startIndex)
{
}

/*	
	parameters:		- startIndex	= The index from which to start shifting elements to the right.
	requirements:	The list needs to be filled up from the left to the right (no empty indexes) 
					apart from the startIndex.
	definition:		The lists elements will each be shifted left one position starting from the element 
					at the startIndex up to the last element that is not nullptr.
*/
void NodeList::ShiftLeftFromIndex(const int startIndex)
{
}

/*	
	definition:		Fills the list from left to right leaving no empty indexes.
*/
void NodeList::FillFromLeft()
{
}

/*	
	parameter:		- index		= The index at which the Node will be added.
	Definition:		Adds a node to the list at the given index.
*/
void NodeList::AddOnIndex(const int index)
{

}

/*
	parameters:		- index		= The index at which the Node will deleted.
	definition:		Deletes the node from the list at the given index.
	result:			The node that was deleted.
*/
Node NodeList::PopOnIndex(const int index)
{
	return Node{};
}

/*
	definition:		Sorts the nodes in the list from left to right with increasing m_globalGoals.
*/
void NodeList::Sort()
{
}

Node::Node()
	:m_pParent(nullptr),
	m_Obstacle(false),
	m_Visited(false),
	m_GlobalGoal(9999.99f),
	m_LocalGoal(9999.99f),
	m_GridPos(GridPosition())
{
}

Node::Node(bool obstacle, bool initialized, GridPosition gridPos)
	:m_pParent(nullptr),
	m_Obstacle(obstacle),
	m_Visited(false),
	m_GlobalGoal(9999.99f),
	m_LocalGoal(9999.99f),
	m_GridPos(gridPos)
{
}

Node::~Node()
{
}

NodeMap::NodeMap()
	:m_SizeX(1), m_SizeY(1), m_pMap(nullptr)
{
}

NodeMap::NodeMap(const int sizeX, const int sizeY, Node* mapArray)
	:m_SizeX(sizeX), m_SizeY(sizeY),m_pMap(mapArray)
{
}

NodeMap::~NodeMap()
{
	delete[] m_pMap;
	m_pMap = nullptr;
}

void NodeMap::UpdateNodeState(const int x, const int y, bool state)
{
	m_pMap[y * m_SizeX + x].m_Obstacle = state;
}

Node NodeMap::GetNode(const int x, const int y)
{
	const int index{ int(m_SizeX) * y + x };
	return m_pMap[index];
}

Node NodeMap::GetNodeOnGridPos(GridPosition gridPos)
{
	return GetNode(gridPos.x, gridPos.y);
}

NodeNeighbours* NodeMap::GetNeighbours(const int x, const int y)
{
	if (x == 0)
	{
		if (y == 0)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x + 1, y),
														GetNode(x, y + 1)} };
		}
		else if (y == m_SizeY)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x + 1, y),
														GetNode(x, y - 1) } };
		}
		else
		{
			return new NodeNeighbours{ 2, new Node[3]{ GetNode(x, y - 1),
														GetNode(x + 1, y),
														GetNode(x, y + 1) } };
		}
	}
	else if (x == m_SizeX)
	{
		if (y == 0)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x - 1, y),
														GetNode(x, y + 1) } };
		}
		else if (y == m_SizeY)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x - 1, y),
														GetNode(x, y - 1) } };
		}
		else
		{
			return new NodeNeighbours{ 2, new Node[3]{ GetNode(x, y - 1),
														GetNode(x, y + 1),
														GetNode(x - 1, y) } };
		}
	}
	else if (y == 0)
	{
		if (x == 0)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x + 1, y),
														GetNode(x, y + 1) } };
		}
		else if (x == m_SizeX)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x - 1, y),
														GetNode(x, y + 1) } };
		}
		else
		{
			;
			return new NodeNeighbours{ 3,  new Node[3]{ GetNode(x + 1, y),
														GetNode(x, y + 1),
														GetNode(x - 1, y) } };
		}
	}
	else if (y == m_SizeY)
	{
		if (x == 0)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x + 1, y),
														GetNode(x, y - 1) } };
		}
		else if (x == m_SizeX)
		{
			return new NodeNeighbours{ 2, new Node[2]{ GetNode(x - 1, y),
														GetNode(x, y - 1) } };
		}
		else
		{
			return new NodeNeighbours{ 3, new Node[3]{ GetNode(x, y - 1),
														GetNode(x + 1, y),
														GetNode(x - 1, y) } };
		}
	}
	else
	{
		return new NodeNeighbours{ 4, new Node[4]{ GetNode(x, y - 1),
													GetNode(x + 1, y),
													GetNode(x, y + 1),
													GetNode(x - 1, y) } };
	}

}

NodeNeighbours::NodeNeighbours(const int arraySize, Node* nodes)
	:m_Count(arraySize), m_pNodes()
{
}

NodeNeighbours::~NodeNeighbours()
{
	delete[] m_pNodes;
	m_pNodes = nullptr;
}
