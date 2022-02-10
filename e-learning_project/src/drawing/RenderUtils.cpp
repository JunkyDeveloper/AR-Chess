#include "../../include/drawing/RenderUtils.h"

namespace RenderUtils
{
	std::optional<Move> move;
	std::mutex lock_move;
	std::optional<Move> getMove()
	{
		std::lock_guard<std::mutex> lock(lock_move);
		return move;
	}
	void setMove(Move m)
	{
		std::lock_guard<std::mutex> lock(lock_move);
		move = m;
	}
	void clear()
	{
		std::lock_guard<std::mutex> lock(lock_move);
		move = std::nullopt;
	}
}