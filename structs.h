#pragma once
#include <string>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );

	float x;
	float y;
};



struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	
	float left;
	float bottom;
	float width;
	float height;

};


struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};

struct Vector2f 
{
	Vector2f();
	explicit Vector2f(float x, float y);

	float x;
	float y;
};

struct MatrixChar
{
	int m_SizeX,
		m_SizeY;
	char* m_pMatrix;

	MatrixChar(const int x, const int y, char* charArray);
	~MatrixChar();
};



enum class WorldState {
	danger, passable, impassable, breakable, zombie, player
};

enum class DirectionState {
	up, right, down, left
};

struct GridPosition
{
	int x,
		y;
	int GlobalGoal = 9999;

	GridPosition();
	GridPosition(const int x, const int y);
	~GridPosition();
};

struct MatrixElement 
{
	WorldState m_WorldState;
	Point2f m_Position;
	GridPosition m_GridPos;
	
	MatrixElement();
	explicit MatrixElement(WorldState worldState, Point2f bottomLeft, GridPosition gridPos);
	~MatrixElement();
};

struct Node
{
	Node* m_pParent;
	bool m_Obstacle,
			m_Visited;
	float m_GlobalGoal;
	int m_LocalGoal;
	GridPosition m_GridPos;

	Node();
	Node(bool obstacle, GridPosition gridPos);
	~Node();
};

struct NodeNeighbours
{
	const int m_Count;
	Node* m_pNodes;

	NodeNeighbours(const int arraySize, Node* nodes);
	~NodeNeighbours();
};

struct NodeList
{
	int m_Size;
	int m_NodeCount;
	GridPosition* m_pList;

	NodeList();
	NodeList(const int size, const int nodeCount, GridPosition* pPosArray);
	~NodeList();

	void SwapElements(const int index1, const int index2);
	void ShiftRightFromIndex(const int startIndex = 0);
	void ShiftLeftFromIndex(const int startIndex = 1);
	void FillFromLeft();
	void AddOnIndex(const int index, GridPosition pos);
	GridPosition PopOnIndex(const int index);
	void IncNodeCount();
	void DecNodeCount();
	void Sort();
};

struct Neighbours
{
	const int m_Count;
	MatrixElement* m_pElements;

	Neighbours(const int arraySize, MatrixElement* elements);
	~Neighbours();
};

struct Enemy
{
	GridPosition m_GridPos;
	DirectionState m_dir;
	bool dead{ false };

	Enemy();
	Enemy(GridPosition gridPos, DirectionState dir);
	~Enemy();
};

struct Player
{
	GridPosition m_GridPos;
	DirectionState m_dir;
	bool dead{ false };

	Player();
	Player(GridPosition gridPos, DirectionState dir);
	~Player();


};

struct Bullet
{
	GridPosition m_GridPos;
	DirectionState m_dir;

	Bullet();
	Bullet(GridPosition gridPos, DirectionState dir);
	~Bullet();
};

struct Matrix
{
	int m_SizeX,
		m_SizeY;
	MatrixElement* m_pMatrix;

	Matrix();
	explicit Matrix(const int sizeX, const int sizeY, MatrixElement* pMatrix);
	~Matrix();

	MatrixElement GetElement(const int x, const int y);
	Neighbours* GetNeighbours(const int x, const int y);
	void UpdateCellState(const int x, const int y, WorldState state);
	bool MoveE(Enemy& enemy, const Neighbours& neighbours);
	bool MoveP(Player& player, const Neighbours& neighbours);
	bool MoveB(Bullet& bullet, const Neighbours& neighbours);
};

struct NodeMap
{
	int m_SizeX,
		m_SizeY;
	Node* m_pMap;

	NodeMap();
	NodeMap(const int sizeX, const int sizeY, Node* mapArray);
	~NodeMap();

	void UpdateNodeState(const int x, const int y, bool state);
	Node GetNode(const int x, const int y);
	Node* GetNodeOnGridPos(GridPosition gridPos);
	NodeNeighbours* GetNeighbours(const int x, const int y);
};

