#pragma once
#include "../main.h"
#include <array>
namespace DrawFigures
{
	void drawQueenWhite(std::array<float,16>);
	void drawPawnWhite(std::array<float,16>);
	void drawRookWhite(std::array<float,16>);
	void drawBishop(std::array<float,16>);
	void drawBishop2(std::array<float,16>);
	void drawKingWhite(std::array<float,16>);
	void drawKnightWhite(std::array<float,16>);
	void drawKnightBlack(std::array<float, 16> tm);
	void drawKingBlack(std::array<float, 16>);
	void drawBishop2Black(std::array<float, 16>);
	void drawBishopBlack(std::array<float, 16>);
	void drawRookBlack(std::array<float, 16>);
	void drawPawnBlack(std::array<float, 16>);
	void drawQueenBlack(std::array<float, 16>);
}