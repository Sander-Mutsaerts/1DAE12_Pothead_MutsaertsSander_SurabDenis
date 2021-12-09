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

Enemy* g_Enemy{nullptr};
Player* g_Player{nullptr};
Bullet* g_Bullet{nullptr};
// Declare your own functions here
void InitializeMatrix();
void DrawGrid();
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
