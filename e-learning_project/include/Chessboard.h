//
//  Chessboard.hpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//
#pragma once
#include <iostream>
#include <stdio.h>
#include "Field.h"
#include <tuple>
#include <optional>
#include <mutex>

class ChessBoard
{
    // TODO contructors definieren
public:
    std::vector<Field> getMoves(Field const&);
    Field& getField(char, int);
    void addFigureOnField(Figure const&, Field const&);
    bool moveFigure(Figure const&, Field, Field, std::vector<Field>);

    std::vector<std::vector<Field> > getBoard() const;
    void setBoard(std::vector<std::vector<Field> >);
    void drawBoard();
    std::optional<Field> locateField(std::tuple<int, int>point);
    void clear();
    void copyFigures(const ChessBoard&);
    void replaceTransformation(const ChessBoard&);
    void replaceTransformation(const std::vector<std::vector<Field>>&);

private:
    std::vector<std::vector<Field>> board;
    // Convention: figure_color e.g. pawn_white
    // figure names: pawn, knight, bishop, rook, queen, king

    // return vector of all possible fields e.g. E5
    std::vector<Field> movesOfPawn(Field const&);
    std::vector<Field> movesOfKnight(Field const&);
    std::vector<Field> movesOfBishop(Field const&);
    std::vector<Field> movesOfRook(Field const&);
    std::vector<Field> movesOfQueen(Field const&);
    std::vector<Field> movesOfKing(Field const&);

    std::vector<std::pair<Figure, Field> > getOpponentsFigurePositions(bool);
    bool isKingInChess(Field const&, bool, const Move&);

    std::vector<Field> allPossVerticalOf(Field const&);
    std::vector<Field> allPossHorizontalOf(Field const&);
    std::vector<Field> allPossDiagonalLeftOf(Field const&);
    std::vector<Field> allPossDiagonalRightOf(Field const&);

    // only for white figures
    std::optional<Field> directInFrontOf(Field const&);
    std::optional<Field> directBehindOf(Field const&);
    std::optional<Field> leftOf(Field const&);
    std::optional<Field> leftDiagonalTopOf(Field const&);
    std::optional<Field> leftDiagonalBottomOf(Field const&);
    std::optional<Field> rightOf(Field const&);
    std::optional<Field> rightDiagonalTopOf(Field const&);
    std::optional<Field> rightDiagonalBottomOf(Field const&);

    // helpers
    static bool movePossible(Field const&, bool);
    // void printFields(std::vector<Field>);
};
