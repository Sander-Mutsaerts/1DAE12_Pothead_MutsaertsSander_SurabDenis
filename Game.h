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
int g_CellPixelSize{};
int g_NrFrames{0};
Matrix* g_pMatrix{ new Matrix{} };

Enemy* g_pEnemy{nullptr};
Player* g_pPlayer{nullptr};
Bullet* g_pBullet{nullptr};

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

Texture g_BulletTextures[g_AmountOfText]{};
Texture* g_pBulletTextures{};

// Declare your own functions here
void InitializeMatrix();
void InitializePlayer();
void InitializeEnemy();
void InitializeGun();
void InitializeBullet();
void InitializeGrid();
void DrawGrid();
void DrawTextures();
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
