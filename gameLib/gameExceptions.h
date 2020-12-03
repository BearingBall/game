#pragma once
#include <exception>

class SDL_GraphicsError final : std::exception
{
	const char* what() const noexcept override
	{
		return "SDL_GraphicsError\n";
	}
};

class MemoryError final : std::exception
{
	const char* what() const noexcept override
	{
		return "MemoryError\n";
	}
};

class InputDataCorruption final : std::exception
{
	const char* what() const noexcept override
	{
		return "InputDataCorruption\n";
	}
};