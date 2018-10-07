#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "Resources.h"

#define ERROR_MSGBOX_TITLE "Error"

namespace Util
{
	static bool loadPng(const char* filename, SDL_Surface* &surface)
	{
		// LOAD PNG FROM FILE TO SURFACE
		std::string path = DEFAULT_TEXTURE_PATH;
		path.append(filename).append(".png");
		SDL_Surface* tempSurface = IMG_Load(path.c_str());
		if (tempSurface == NULL)
		{
			// LOG ERROR
			return false;
		}
		else
		{
			//Convert surface to screen format
			surface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32, NULL);
			if (surface == NULL)
			{
				std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
				return false;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(tempSurface);
		}

		return true;
	}

	static void showMessageBox(std::string message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_MSGBOX_TITLE, message.c_str(), NULL);
	}
}

#endif // !UTIL_H