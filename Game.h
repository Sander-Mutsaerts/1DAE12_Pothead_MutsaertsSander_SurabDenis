#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Pothead - Mutsaerts Sander, Surab Denis - 1DAE12" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
/*	- g_GridScaler =	Default must be one, will use GCD of the resolution to get a standard grid
*/
const int g_GridScaler{2};
bool g_SpeedChecker[4]{false, false, false, false};
int g_CellPixelSize{};
int g_NrFrames{};
int g_DevisorSpeedP{15};
int g_DevisorSpeedE{ g_DevisorSpeedP };// the bigger the slower the game goes
bool g_DidZombieCaughtUpToThePlayer{ false };
bool g_DidTheTimeRunOut{ false };
Matrix* g_pMatrix{ new Matrix{} };
NodeMap* g_pNodeMap{ new NodeMap{} };
Texture g_TimerText{};
const Color4f g_TimerColour{1,1,1,1};
const int g_TimerFontSize{48};
int g_MaxTime{100};
int g_Timer{ g_MaxTime };
void UpdateTimer(float elapsedTime);

bool g_WasBeartTrapPlacedByPlayer{ false };
Point2f g_BearTrapPos{};

Texture g_EndScreenWinText{};
Texture g_EndScreenLooseText{};
const Color4f g_EndScreenFontColurForText{ 0,0.5f,1,1 };
const int g_EndScreenFontSizeForText{ 50 };

Enemy* g_pEnemy{nullptr};
Player* g_pPlayer{nullptr};
Bullet* g_pBullet{nullptr};
GridPosition* g_pCurrentNode{ new GridPosition{} };

//Textures globals
// g_AmountOfText represent the number of directions our objects can move around the grid basic is 4 later can work up to 8 (diagonal)
const int g_AmountOfText{4};
Texture g_PlayerTextures[g_AmountOfText]{};
Texture* g_pPlayerTexture{nullptr};

Texture g_GunTextures[g_AmountOfText]{};
Texture* g_pGunTextures{};

Texture g_EnemyTextures[g_AmountOfText]{};
Texture* g_pEnemyTexture{nullptr};

Texture g_Unpassable{};
Texture g_Passable{};

Texture g_TrapTexture{};

// Declare your own functions here
void InitializeMatrix();
void InitializePlayer();
void InitializeEnemy();
void InitializeGun();
void InitializeBullet();
void InitializeTrap();
void InitializeGrid();
void InitializeBackgroundMusic();
void InitializeTimer();
void InitializeEndScreenText();
void DrawGrid();
void DrawTextures();
void DrawTimer();
void UpdateNodes();
void UpdateSpeed();
float Heuristic(GridPosition pos, GridPosition endPos);
bool AStar();
GridPosition FindMoveEnemy(GridPosition currentPos);
DirectionState FindMoveDir(GridPosition enemy, GridPosition move);
void KillEnemy(bool moved);
void KillPlayer(bool moved);
void DrawEndScreen();


#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
