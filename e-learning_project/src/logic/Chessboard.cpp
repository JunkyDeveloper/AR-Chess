//
//  Chessboard.cpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//

#include <algorithm>
#include <optional>
#include "../../include/Chessboard.h"
#include "../../include/ChessboardTools.h"

// ---------------------------- ChessBoard ----------------------------
std::mutex lock_board;
std::vector<Field> ChessBoard::getMoves(Field const& field)
{
    // TODO check if king is in chess if you move a figure
	// figure names: pawn, knight, bishop, rook, queen, king
	if (field.getEmpty())
	{
		return std::vector<Field>();
	}
	Figure figure = field.getFigure();

	switch (figure.getName().at(0))
	{
	case 'P':
		return movesOfPawn(field);
	case 'N':
		return movesOfKnight(field);
	case 'B':
		return movesOfBishop(field);
	case 'R':
		return movesOfRook(field);
	case 'Q':
		return movesOfQueen(field);
	case 'K':
		return movesOfKing(field);
	default:
		return std::vector<Field>();
	}
}

std::vector<Field> ChessBoard::movesOfPawn(Field const& field)
{
	std::vector<Field> possMoves;
	if (field.getFigure().getIsWhite())
	{ // white
		// Moves forward
		std::optional<Field> front = directInFrontOf(field);
		// check if front exists (std::optional)
		if (front && front.value().getEmpty())
		{
			possMoves.push_back(front.value());
			if (field.getNumber() == 2)
			{
				std::optional<Field> twoInFront = directInFrontOf(front.value());
				// check if twoInFront exists (std::optional)
				if (twoInFront && twoInFront.value().getEmpty())
				{
					possMoves.push_back(twoInFront.value());
				}
			}
		}

		// Kick out
		std::optional<Field> frontLeft = leftDiagonalTopOf(field);
		if (frontLeft && !frontLeft.value().getEmpty() && !frontLeft.value().getFigure().getIsWhite())
		{
			possMoves.push_back(frontLeft.value());
		}

		std::optional<Field> frontRight = rightDiagonalTopOf(field);
		if (frontRight && !frontRight.value().getEmpty() && !frontRight.value().getFigure().getIsWhite())
		{
			possMoves.push_back(frontRight.value());
		}
	}
	else
	{ // black
		// Moves forward (backward from white point of view)
		std::optional<Field> front = directBehindOf(field);
		// check if front exists (std::optional)
		if (front && front.value().getEmpty())
		{
			possMoves.push_back(front.value());
			if (field.getNumber() == 7)
			{
				std::optional<Field> twoInFront = directBehindOf(front.value());
				// check if twoInFront exists (std::optional)
				if (twoInFront && twoInFront.value().getEmpty())
				{
					possMoves.push_back(twoInFront.value());
				}
			}
		}

		// Kick out
		// left of black pawn is right of white pawn
		std::optional<Field> frontLeft = leftDiagonalTopOf(field);
		if (frontLeft && !frontLeft.value().getEmpty() && frontLeft.value().getFigure().getIsWhite())
		{
			possMoves.push_back(frontLeft.value());
		}

		std::optional<Field> frontRight = rightDiagonalTopOf(field);
		if (frontRight && !frontRight.value().getEmpty() && frontRight.value().getFigure().getIsWhite())
		{
			possMoves.push_back(frontRight.value());
		}
	}
	return possMoves;
}

std::vector<Field> ChessBoard::movesOfKnight(Field const& field)
{
	std::vector<Field> possMoves;
	std::optional<Field> testField;

	// 2 up
	// 1 left
	if (field.getLetter() - 1 >= 'A' && field.getNumber() + 2 < 9)
	{
		testField = getField(field.getLetter() - 1, field.getNumber() + 2);
		if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
			possMoves.push_back(testField.value());
	}

	// 2 up
	// 1 right
	if (field.getLetter() + 1 <= 'H' && field.getNumber() + 2 < 9)
	{
		testField = getField(field.getLetter() + 1, field.getNumber() + 2);
		if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
			possMoves.push_back(testField.value());
	}

	// 2 down
	// 1 left
	if (field.getLetter() - 1 >= 'A' && field.getNumber() - 2 > 0)
	{
		testField = getField(field.getLetter() - 1, field.getNumber() - 2);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}

	// 1 right
	// 2 down
	if (field.getLetter() + 1 <= 'H' && field.getNumber() - 2 > 0)
	{
		testField = getField(field.getLetter() + 1, field.getNumber() - 2);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}

	// 2 left
	// 1 up
	if (field.getLetter() - 2 >= 'A' && field.getNumber() + 1 < 9)
	{
		testField = getField(field.getLetter() - 2, field.getNumber() + 1);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}

	// 2 left
	// 1 down
	if (field.getLetter() - 2 >= 'A' && field.getNumber() - 1 > 0)
	{
		testField = getField(field.getLetter() - 2, field.getNumber() - 1);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}

	// 2 right
	// 1 up
	if (field.getLetter() + 2 <= 'H' && field.getNumber() + 1 < 9)
	{
		testField = getField(field.getLetter() + 2, field.getNumber() + 1);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}

	// 2 left
	// 1 down
	if (field.getLetter() + 2 <= 'H' && field.getNumber() - 1 > 0)
	{
		testField = getField(field.getLetter() + 2, field.getNumber() - 1);
        if (testField && movePossible(testField.value(), field.getFigure().getIsWhite()))
            possMoves.push_back(testField.value());
	}
	return possMoves;
}

std::vector<Field> ChessBoard::movesOfBishop(Field const& field)
{
	std::vector<Field> possMoves;
	std::vector<Field> diagLeftFields = allPossDiagonalLeftOf(field);
	std::vector<Field> diagRightFields = allPossDiagonalRightOf(field);
	for (const auto& possField : diagLeftFields)
	{
		Field& onBoard = getField(possField.getLetter(), possField.getNumber());
		// TODO if index isn't found exception is thrown
		// white figures cannot be kicked out or jumped over
		if (!movePossible(onBoard, field.getFigure().getIsWhite()))
		{
			break;
		}
		possMoves.push_back(possField);
	}

	for (const auto& possField : diagRightFields)
	{
		Field& onBoard = getField(possField.getLetter(), possField.getNumber());
		// TODO if index isn't found exception is thrown
		// white figures cannot be kicked out or jumped over
		if (!movePossible(onBoard, field.getFigure().getIsWhite()))
		{
			break;
		}
		possMoves.push_back(possField);
	}
	return possMoves;
}

std::vector<Field> ChessBoard::movesOfRook(Field const& field)
{
	std::vector<Field> possMoves;
	auto vertFields = allPossVerticalOf(field);
	auto horFields = allPossHorizontalOf(field);
	for (const auto& possField : vertFields)
	{
		Field& onBoard = getField(possField.getLetter(), possField.getNumber());
		// TODO if index isn't found exception is thrown
		// white figures cannot be kicked out or jumped over
		if (movePossible(onBoard, field.getFigure().getIsWhite()))
		{
		    possMoves.push_back(possField);
		}
	}

	for (const auto& possField : horFields)
	{
		Field& onBoard = getField(possField.getLetter(), possField.getNumber());
		// TODO if index isn't found exception is thrown
		// white figures cannot be kicked out or jumped over
		if (movePossible(onBoard, field.getFigure().getIsWhite()))
		{
		    possMoves.push_back(possField);
		}
	}
	return possMoves;
}

std::vector<Field> ChessBoard::movesOfQueen(Field const& field)
{
	std::vector<Field> possMoves;
	// all cross fields
	std::vector<Field> crossMoves = movesOfRook(field);
	for (const auto& move : crossMoves)
	{
		possMoves.push_back(move);
	}
	// all diagonal fields
	std::vector<Field> diagMoves = movesOfBishop(field);
	for (const auto& move : diagMoves)
	{
		possMoves.push_back(move);
	}
	return possMoves;
}

std::vector<Field> ChessBoard::movesOfKing(Field const& field)
{
    std::vector<Field> possMoves;

    // Moves vertically
    std::optional<Field> testField = directInFrontOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    testField = directBehindOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    // Moves horizontally
    testField = rightOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    testField = leftOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    // Move diagonal top
    testField = leftDiagonalTopOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    testField = rightDiagonalTopOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    // Moves diagonal back
    testField = leftDiagonalBottomOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    testField = rightDiagonalBottomOf(field);
    // check if testField exists (std::optional)
    if (testField && movePossible(testField.value(), field.getFigure().getIsWhite())) {
        possMoves.push_back(testField.value());
    }

    return possMoves;
}

std::vector<std::pair<Figure, Field> > ChessBoard::getOpponentsFigurePositions(bool opponentsColor)
{
    std::vector<std::pair<Figure, Field>> oppFigures;
    for (auto letter : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'})
    {
        for (auto number: {1 ,2, 3, 4, 5, 6, 7, 8})
        {
            std::optional<Field> field = getField(letter, number);
            // check if figure on field is color of opponent
            if (field && !field.value().getEmpty() && field.value().getFigure().getIsWhite() == opponentsColor)
            {
                oppFigures.emplace_back(field->getFigure(), field.value());
            }
        }
    }
	return oppFigures;
}

bool ChessBoard::isKingInChess(Field const& fieldOfOwnKing, bool playersColor, const Move& moveToCheck)
{
    // find opponents figures on field
    std::vector<Field> possMoves;
    auto boardAfterMove = getBoard();
    ChessBoard newBoard{};
    newBoard.board = boardAfterMove;
    auto movesOfOwnKing = movesOfKing(fieldOfOwnKing);
    newBoard.moveFigure(moveToCheck.figure, moveToCheck.from, moveToCheck.to, movesOfOwnKing);

    std::vector<std::pair<Figure, Field> > oppFigures = newBoard.getOpponentsFigurePositions(!playersColor);

    for (auto& [fig, field] : oppFigures) {
        switch (fig.getName().at(0)) {
            case 'K':
                possMoves = movesOfKing(field);
                break;
            case 'Q':
                possMoves = movesOfQueen(field);
                break;
            case 'B':
                possMoves = movesOfBishop(field);
                break;
            case 'N':
                possMoves = movesOfKnight(field);
                break;
            case 'R':
                possMoves = movesOfRook(field);
                break;
            case 'P':
                possMoves = movesOfPawn(field);
                break;
            default:
                break;
        }
        // return true if king is in chess
        return std::find(possMoves.begin(), possMoves.end(), fieldOfOwnKing) != possMoves.end();
    }
}

std::vector<std::pair<Field, Field> > castling(bool playerColor)
{
	std::vector<std::pair<Field, Field> > possMoves;
	// TODO check that king and rook haven't moved yet
	//   TODO we would need to now all moves from beginning
	// TODO we would return std::vector<std::pair<Field, Field > > because we need to move two figures
	std::pair<Field, Field> queenSide;
	std::pair<Field, Field> kingSide;

	if (playerColor)
	{
		// castling king's side (kleine Rochade)
		Field field_rook{ 'F', 1 };
		Field field_king{ 'G', 1 };
		queenSide = std::make_pair(field_rook, field_king);
		// castling queen's sie (grosse Rochade)
		field_rook = Field{ 'D', 1 };
		field_king = Field{ 'C', 1 };
		kingSide = std::make_pair(field_rook, field_king);
	}
	else
	{
		// castling king's side (kleine Rochade)
		Field field_rook{ 'F', 8 };
		Field field_king{ 'G', 8 };
		queenSide = std::make_pair(field_rook, field_king);
		// castling queen's sie (grosse Rochade)
		field_rook = Field{ 'D', 1 };
		field_king = Field{ 'C', 1 };
		kingSide = std::make_pair(field_rook, field_king);
	}
	return std::vector{ queenSide, kingSide };
}

bool ChessBoard::movePossible(Field const& field, bool playersColor)
{
    bool inBorderVertical = field.getNumber() >= 1 && field.getNumber() <= 8;
    int actualLetter = (int)field.getLetter() - 65;
    bool inBorderHorizontal = actualLetter >= 0 && actualLetter <= 7;
    if (playersColor) { // white
        // TODO check if king is in chess
        return (inBorderVertical && inBorderHorizontal && (field.getEmpty() || (!field.getEmpty() && !field.getFigure().getIsWhite())));
    }
    // black
    // TODO check if king is in chess
    return (inBorderVertical && inBorderHorizontal && (field.getEmpty() || (!field.getEmpty() && field.getFigure().getIsWhite())));
}

// returns the field with definition letter and number
Field& ChessBoard::getField(char letter, int number)
{
	std::lock_guard<std::mutex> lock(lock_board);
	bool inBorderVertical = number >= 1 && number <= 8;
	int actualLetter = (int)letter - 65;
	bool inBorderHorizontal = actualLetter >= 0 && actualLetter <= 7;
	if (inBorderVertical && inBorderHorizontal)
	{
		return board[8 - number][(int)letter - 65];
	}
	std::string s(1, letter);
	throw std::invalid_argument("indices " + s + std::to_string(number) + " not found");
}

std::vector<Field> ChessBoard::allPossVerticalOf(Field const& field)
{
	std::vector<Field> allPossFields;
	std::optional<Field> nextField = directInFrontOf(field);

    // check if nextField exists (std::optional)
	while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
		if (nextField.value().getEmpty()) {
		    nextField = directInFrontOf(nextField.value());
		} else {
		    break;
		}
	}

	nextField = directBehindOf(field);
	// check if nextField exists (std::optional)
	while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = directBehindOf(nextField.value());
        } else {
            break;
        }
    }
	return allPossFields;
}

std::vector<Field> ChessBoard::allPossHorizontalOf(Field const& field)
{
	std::vector<Field> allPossFields;
	std::optional<Field> nextField = leftOf(field);
	// go to left most field
	// check if nextField exists (std::optional)
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = leftOf(nextField.value());
        } else {
            break;
        }
	}
	// go to right most field
	nextField = rightOf(field);
	// check if nextField exists (std::optional)
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = rightOf(nextField.value());
        } else {
            break;
        }
	}
	return allPossFields;
}

std::optional<Field> ChessBoard::directInFrontOf(Field const& field)
{
	if (field.getNumber() + 1 < 9)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter(), field.getNumber() + 1);
	return std::nullopt;
}

std::optional<Field> ChessBoard::directBehindOf(Field const& field)
{
	if (field.getNumber() - 1 > 0)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter(), field.getNumber() - 1);
	return std::nullopt;
}

// All moves to the left
std::optional<Field> ChessBoard::leftOf(Field const& field)
{
	if (field.getLetter() - 1 >= 'A')
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() - 1, field.getNumber());
	return std::nullopt;
}

std::optional<Field> ChessBoard::leftDiagonalTopOf(Field const& field)
{
	if (field.getLetter() - 1 >= 'A' && field.getNumber() + 1 < 9)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() - 1, field.getNumber() + 1);
	return std::nullopt;
}

std::optional<Field> ChessBoard::leftDiagonalBottomOf(Field const& field)
{
	if (field.getLetter() - 1 >= 'A' && field.getNumber() - 1 > 0)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() - 1, field.getNumber() - 1);
	return std::nullopt;
}

// All moves to the right
std::optional<Field> ChessBoard::rightOf(Field const& field)
{
	if (field.getLetter() + 1 <= 'H')
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() + 1, field.getNumber());
	return std::nullopt;
}

std::optional<Field> ChessBoard::rightDiagonalTopOf(Field const& field)
{
	if (field.getLetter() + 1 <= 'H' && field.getNumber() + 1 < 9)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() + 1, field.getNumber() + 1);
	return std::nullopt;
}

std::optional<Field> ChessBoard::rightDiagonalBottomOf(Field const& field)
{
	if (field.getLetter() + 1 <= 'H' && field.getNumber() - 1 > 0)
		// TODO if index isn't found exception is thrown
		return getField(field.getLetter() + 1, field.getNumber() - 1);
	return std::nullopt;
}

//
std::vector<Field> ChessBoard::allPossDiagonalLeftOf(Field const& field)
{
	std::optional<Field> nextField = leftDiagonalTopOf(field);
	std::vector<Field> allPossFields;
	// go to top left field
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = leftDiagonalTopOf(nextField.value());
        } else {
            break;
        }
	}
	// go to bottom right field
	nextField = rightDiagonalBottomOf(field);
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = rightDiagonalBottomOf(nextField.value());
        } else {
            break;
        }
	}
	return allPossFields;
}

std::vector<Field> ChessBoard::allPossDiagonalRightOf(Field const& field)
{
	std::optional<Field> nextField = rightDiagonalTopOf(field);
	std::vector<Field> allPossFields;
	// go to top right field
	// check if nextField exists (std::optional)
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = rightDiagonalTopOf(nextField.value());
        } else {
            break;
        }
	}
	// go to bottom left field
	nextField = leftDiagonalBottomOf(field);
	// check if nextField exists (std::optional)
    while (nextField && movePossible(nextField.value(), field.getFigure().getIsWhite()))
	{
		allPossFields.push_back(nextField.value());
        if (nextField.value().getEmpty()) {
            nextField = leftDiagonalBottomOf(nextField.value());
        } else {
            break;
        }
	}

	return allPossFields;
}

void ChessBoard::addFigureOnField(Figure const& figure, Field const& field)
{
	Field& onBoard = getField(field.getLetter(), field.getNumber());
	// TODO if index isn't found exception is thrown
	onBoard.setFigure(figure);
}

void ChessBoard::clear()
{
	copyFigures(ChessboardTools::createEmptyBoard());
}

bool ChessBoard::moveFigure(Figure const& figure, Field oldField, Field newField, std::vector<Field> possMoves)
{
	std::lock_guard<std::mutex> lock(lock_board);
	// check if move is possible
	if (std::find(possMoves.begin(), possMoves.end(), newField) != possMoves.end())
	{
		if (!newField.getEmpty())
		{
			if (newField.getFigure().getIsWhite() == oldField.getFigure().getIsWhite())
			{
				std::cout << "cannot move figure to field where own figure is placed" << std::endl;
				return false;
			}
		}
		// oldField.setFigure(nullptr); // TODO remove figure from field
		oldField.setEmpty(true);
		newField.setFigure(figure);
		return true;
	}
	else
	{
		// we don't check moves for black figures (yet)
		if (!figure.getIsWhite())
		{
			if (!newField.getEmpty())
			{
				if (!newField.getFigure().getIsWhite())
				{
					std::cout << "cannot move figure to field where own figure is placed" << std::endl;
					return false;
				}
				oldField.setEmpty(true);
				newField.setFigure(figure);
				return true;
			}
		}
		return false;
	}
}

std::vector<std::vector<Field> > ChessBoard::getBoard() const
{
	std::lock_guard<std::mutex> lock(lock_board);
	return board;
}

void ChessBoard::setBoard(std::vector<std::vector<Field> > b)
{
	std::lock_guard<std::mutex> lock(lock_board);
	board = b;
}

void ChessBoard::drawBoard()
{
	std::cout << "   ___A___ ___B___ ___C___ ___D___ ___E___ ___F___ ___G___ ___H___"
		<< "\n";
	std::cout << "   ####### ####### ####### ####### ####### ####### ####### #######"
		<< "\n";

	for (int index = 7; index >= 0; index--)
	{
		std::cout << "   #     # #     # #     # #     # #     # #     # #     # #     #"
			<< "\n";

		std::cout << " " << index + 1 << " ";
		for (auto letter : { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' })
		{
			Field& field = getField(letter, index + 1);
			// TODO if index isn't found exception is thrown
			if (!field.getEmpty())
			{
				std::cout << "# ";
				std::cout << field.getFigure().getName();
				std::cout << " # ";
			}
			else
			{
				std::cout << "#     # ";
			}
		}
		std::cout << "\n";
		std::cout << "   #     # #     # #     # #     # #     # #     # #     # #     #"
			<< "\n";
		std::cout << "   ####### ####### ####### ####### ####### ####### ####### #######"
			<< "\n";
	}

	std::cout << "   ___A___ ___B___ ___C___ ___D___ ___E___ ___F___ ___G___ ___H___" << std::endl;
}

std::optional<Field> ChessBoard::locateField(std::tuple<int, int> point)
{
	std::lock_guard<std::mutex> lock(lock_board);
	auto [x, y] = point;
	cv::Point2f middle = cv::Point2f(x, y);
	for (auto& row : board)
	{
		for (auto& field : row)
		{
			cv::Rect boundingRect(field.getCorners().corner0, field.getCorners().corner3);
			if (middle.inside(boundingRect))
			{
				return field;
			}
		}
	}
	return std::nullopt;
}

void ChessBoard::copyFigures(const ChessBoard& chessboard)
{
	std::lock_guard<std::mutex> lock(lock_board);
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board[i].size(); j++)
		{
			board[i][j].setFigure(chessboard.board[i][j].getFigure());
			board[i][j].setEmpty(chessboard.board[i][j].getEmpty());
		}
}

void ChessBoard::replaceTransformation(const ChessBoard& chessboard) {
	replaceTransformation(chessboard.board);
}

void ChessBoard::replaceTransformation(const std::vector<std::vector<Field>>& board) {
	std::lock_guard<std::mutex> lock(lock_board);
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board[i].size(); j++)
		{
			this->board[i][j].setCorners(board[i][j].getCorners());
			this->board[i][j].transformationMatrix = board[i][j].transformationMatrix;
		}
}