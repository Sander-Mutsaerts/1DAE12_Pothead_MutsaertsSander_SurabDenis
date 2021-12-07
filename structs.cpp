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
	: m_WorldState(worldState), m_Position(bottomLeft), m_GridPosition(gridPos)
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
			if ((enemy.m_GridPos.x == neighbours.m_pElements[i].m_GridPosition.x) 
				&& (enemy.m_GridPos.y - 1 == neighbours.m_pElements[i].m_GridPosition.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPosition.x, 
									neighbours.m_pElements[i].m_GridPosition.y, WorldState::zombie);
					enemy.m_GridPos.y--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::right:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x + 1 == neighbours.m_pElements[i].m_GridPosition.x)
				&& (enemy.m_GridPos.y == neighbours.m_pElements[i].m_GridPosition.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPosition.x,
						neighbours.m_pElements[i].m_GridPosition.y, WorldState::zombie);
					enemy.m_GridPos.x++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::down:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x == neighbours.m_pElements[i].m_GridPosition.x)
				&& (enemy.m_GridPos.y + 1 == neighbours.m_pElements[i].m_GridPosition.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPosition.x,
						neighbours.m_pElements[i].m_GridPosition.y, WorldState::zombie);
					enemy.m_GridPos.y++;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
					return false;
				}
			}
		}
		return false;
		break;
	case DirectionState::left:
		for (int i{}; i < neighbours.m_Count; i++)
		{
			if ((enemy.m_GridPos.x - 1 == neighbours.m_pElements[i].m_GridPosition.x)
				&& (enemy.m_GridPos.y == neighbours.m_pElements[i].m_GridPosition.y))
			{
				if (neighbours.m_pElements[i].m_WorldState == WorldState::passable
					|| neighbours.m_pElements[i].m_WorldState == WorldState::breakable)
				{
					UpdateCellState(enemy.m_GridPos.x, enemy.m_GridPos.y, WorldState::passable);
					UpdateCellState(neighbours.m_pElements[i].m_GridPosition.x,
						neighbours.m_pElements[i].m_GridPosition.y, WorldState::zombie);
					enemy.m_GridPos.x--;

					return true;
				}
				else if (neighbours.m_pElements[i].m_WorldState == WorldState::danger)
				{
					enemy.dead = true;
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
	return false;
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

Player::~Player()
{
}

Bullet::Bullet(DirectionState dir)
	:m_dir(dir)
{
}

Bullet::~Bullet()
{
}
