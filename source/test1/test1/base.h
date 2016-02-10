#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <sstream>

#define NUMBER_FENCE 16
#define NUMBER_FLOOR 12
#define size_modify 2

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

enum GameMode
{
	GM_GAMEPLAY,
	GM_LEVELEDIT
};