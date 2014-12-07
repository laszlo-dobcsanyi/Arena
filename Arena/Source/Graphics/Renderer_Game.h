#ifndef GRAPHICS_RENDER_GAME_H
#define GRAPHICS_RENDER_GAME_H

#include "Game\Hero.h"
#include "Graphics\Shader.h"
#include "Graphics\Camera.h"
#include "Graphics\Renderer.h"

namespace Game_Keys
{
	const unsigned int keys_number = 5;

	enum Keys
	{
		KEY_UP		= 0,
		KEY_LEFT	= 1,
		KEY_DOWN	= 2,
		KEY_RIGHT	= 3,
		KEY_JUMP	= 4
	};
};

class Game;

class Renderer_Game : public Renderer
{
public:
	Renderer_Game(Game *_game);
	virtual ~Renderer_Game();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

private:
	Game *game;

	Camera *camera;

	void DrawBackground();
	void DrawWalls();
	void DrawHeroes(const Hero_Descriptor &_character);

	bool keys[Game_Keys::keys_number];

	Renderer_Game(const Renderer_Game &_other);
	Renderer_Game & operator=(const Renderer_Game  &_other);
};

#endif