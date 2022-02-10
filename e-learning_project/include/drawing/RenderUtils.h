#pragma once
#include "../Puzzles.h"
#include <mutex>
#include <optional>
namespace RenderUtils
{
	std::optional<Move> getMove();
	void setMove(Move m);
	void clear();
}