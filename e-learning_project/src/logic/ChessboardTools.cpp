#include "../../include/ChessboardTools.h"
#include "../../include/Puzzles.h"

Point2f ChessboardTools::getIntersection(Point2f a, Point2f b, Point2f c, Point2f d)
{
    // ab: c1 = a1x + b1y
    float a1 = b.y - a.y;
    float b1 = a.x - b.x;
    float c1 = a1 * a.x + b1 * a.y;

    // cd: c2 = a2x + b2y
    float a2 = d.y - c.y;
    float b2 = c.x - d.x;
    float c2 = a2 * c.x + b2 * c.y;

    // calculate determinante
    float det = a1 * b2 - a2 * b1;

    float x = (b2 * c1 - b1 * c2) / det;
    float y = (a1 * c2 - a2 * c1) / det;

    return Point2f(x, y);
}

void ChessboardTools::setCornerPointsOfFields(contour_f vec, ChessBoard &chessboard)
{ //vec.at(3) upper left corner point, calculate difference in x and y direction
    Point2f vecTopLTopR = Point2f(vec.at(0).x - vec.at(3).x, vec.at(0).y - vec.at(3).y);
    Point2f vecBottomLBottomR = Point2f(vec.at(2).x - vec.at(1).x, vec.at(2).y - vec.at(1).y);

    Point2f vecTopLBottomL = Point2f(vec.at(1).x - vec.at(3).x, vec.at(1).y - vec.at(3).y);
    Point2f vecTopRBottomR = Point2f(vec.at(2).x - vec.at(0).x, vec.at(2).y - vec.at(0).y);

    //root of squared difference
    //float v1_length = sqrt(vecTopLTopR.x * vecTopLTopR.x + vecTopLTopR.y * vecTopLTopR.y);
    //float v2_length = sqrt(vecTopLBottomL.x * vecTopLBottomL.x + vecTopLBottomL.y * vecTopLBottomL.y);

    //normalize vectors to edgeLength of one field
    vecTopLTopR /= 8;
    vecBottomLBottomR /= 8;
    vecTopLBottomL /= 8;
    vecTopRBottomR /= 8;

    //anchor point
    Point2f &anchorTopL = vec.at(3);
    Point2f &anchorTopR = vec.at(0);
    Point2f &anchorBottomR = vec.at(2);
    Point2f &anchorBottomL = vec.at(1);

    for (auto number : {8, 7, 6, 5, 4, 3, 2, 1})
    {
        std::vector<Field *> row;
        for (auto letter : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'})
        {
            int n = letter - 'A';
            int m = 8 - number;
            // Own creation

            Field::cornerPoints cp = {
                ChessboardTools::getIntersection(
                    anchorTopL + n * vecTopLTopR,
                    anchorBottomL + n * vecBottomLBottomR,
                    anchorTopL + m * vecTopLBottomL,
                    anchorTopR + m * vecTopRBottomR), // top left

                ChessboardTools::getIntersection(
                    anchorTopL + (n + 1) * vecTopLTopR,
                    anchorBottomL + (n + 1) * vecBottomLBottomR,
                    anchorTopL + m * vecTopLBottomL,
                    anchorTopR + m * vecTopRBottomR), // top right

                ChessboardTools::getIntersection(
                    anchorTopL + n * vecTopLTopR,
                    anchorBottomL + n * vecBottomLBottomR,
                    anchorTopL + (m + 1) * vecTopLBottomL,
                    anchorTopR + (m + 1) * vecTopRBottomR), // bottom left

                ChessboardTools::getIntersection(
                    anchorTopL + (n + 1) * vecTopLTopR,
                    anchorBottomL + (n + 1) * vecBottomLBottomR,
                    anchorTopL + (m + 1) * vecTopLBottomL,
                    anchorTopR + (m + 1) * vecTopRBottomR) // bottom right
            };

            Field &field = chessboard.getField(letter, number);
            // TODO if index isn't found exception is thrown
            field.setCorners(cp);
        }
    }
}

void ChessboardTools::addFigures(bool white, int startingRow, ChessBoard &chessboard)
{
    // add knights
    std::string knightLabel = "N_";
    knightLabel.push_back(white ? 'W' : 'B');
    Figure knight(knightLabel, white);
    Field field_1('B', startingRow);
    chessboard.addFigureOnField(knight, field_1);
    Field field_2('G', startingRow);
    chessboard.addFigureOnField(knight, field_2);

    // add bishops
    std::string bishopLabel = "B_";
    bishopLabel.push_back(white ? 'W' : 'B');
    Figure bishop(bishopLabel, white);
    Field field_3('C', startingRow);
    chessboard.addFigureOnField(bishop, field_3);
    Field field_4('F', startingRow);
    chessboard.addFigureOnField(bishop, field_4);

    // add rooks
    std::string RookLabel = "R_";
    RookLabel.push_back(white ? 'W' : 'B');
    Figure rook(RookLabel, white);
    Field field_5('A', startingRow);
    chessboard.addFigureOnField(rook, field_5);
    Field field_6('H', startingRow);
    chessboard.addFigureOnField(rook, field_6);

    // add queen
    std::string QueenLabel = "Q_";
    QueenLabel.push_back(white ? 'W' : 'B');
    Figure queen(QueenLabel, white);
    Field field_7('D', startingRow);
    chessboard.addFigureOnField(queen, field_7);

    // add king
    std::string KingLabel = "K_";
    KingLabel.push_back(white ? 'W' : 'B');
    Figure king(KingLabel, white);
    Field field_8('E', startingRow);
    chessboard.addFigureOnField(king, field_8);
}

ChessBoard ChessboardTools::createEmptyBoard()
{
    ChessBoard chessBoard = {};
    std::vector<std::vector<Field> > board;
    for (auto number : {8, 7, 6, 5, 4, 3, 2, 1})
    {
        std::vector<Field> row;
        for (auto letter : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'})
        {
            row.emplace_back(letter, number);
        }
        board.push_back(row);
    }
    chessBoard.setBoard(board);
    return chessBoard;
}

ChessBoard ChessboardTools::createStartingBoard()
{
    ChessBoard chessBoard = createEmptyBoard();

    // add pawns to field
    Figure pawnWhite("P_W", true);
    Figure pawnBlack("P_B", false);
    for (auto letter : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'})
    {
        //        Field field_1{letter, 2};
        chessBoard.addFigureOnField(pawnWhite, {letter, 2});
        Field field_2{letter, 7};
        chessBoard.addFigureOnField(pawnBlack, field_2);
    }
    // add figures
    addFigures(true, 1, chessBoard);  // white
    addFigures(false, 8, chessBoard); // black

    return chessBoard;
}

Field &ChessboardTools::selectField(ChessBoard &board)
{
    char letter;
    int number;
    std::cout << "Enter field letter \n";
    std::cin >> letter;
    // make sure to have upper case letter
    if (letter > 90)
    {
        letter = toupper(letter);
    }
    std::cout << "Enter field number \n";
    std::cin >> number;
    Field &f = board.getField(letter, number);
    // TODO if index is not found exception is thrown
    //std::cout << f.getLetter() << " " << f.getNumber() << std::endl;

    return f;
}

/*
* Example from https://python-chess.readthedocs.io/en/latest/index.html
>>> board = chess.Board("r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4")
>>> print(board)
	r . b q k b . r
	p p p p . Q p p
	. . n . . n . .
	. . . . p . . .
	. . B . P . . .
	. . . . . . . .
	P P P P . P P P
	R N B . K . N R

	white -> upper case
	black -> lower case

Our Board is vector of fields (std::vector<std::vector<Field >>)
*/

std::string ChessboardTools::chessboardToString(std::vector<std::vector<Field> > board)
{
    std::string boardString;

    for (auto i = 0; i < 8; ++i)
    {
        for (auto j = 0; j < 8; ++j)
        {
            Field field = board.at(i).at(j);
            int countEmpty{0};
            while (field.getEmpty() && j < 8)
            {
                ++countEmpty;
                ++j;
                if (j < 8)
                {
                    field = board.at(i).at(j);
                }
            }
            if (countEmpty > 0)
            {
                std::string s = std::to_string(countEmpty);
                boardString += s;
                j += countEmpty;
            }
            if (j > 7)
                continue;

            Figure figure = field.getFigure();
            if (figure.getName().at(2) == 'W')
            {
                boardString += figure.getName().at(0);
            }
            else
            {
                // convert to lower case
                char fig = figure.getName().at(0);
                boardString += (char)(fig + 32);
            }
        }
        // don't add / at end
        if (i < 7)
            boardString += "/";
    }
    return boardString;
}

/*
* Example from https://python-chess.readthedocs.io/en/latest/index.html
>>> board = chess.Board("r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4")
>>> print(board)
    r . b q k b . r
    p p p p . Q p p
    . . n . . n . .
    . . . . p . . .
    . . B . P . . .
    . . . . . . . .
    P P P P . P P P
    R N B . K . N R

    white . upper case
    black . lower case

Our Board is vector of fields (std::vector<std::vector<Field >>)
*/
ChessBoard ChessboardTools::stringToChessboard(const std::string &boardString)
{
    ChessBoard chessboard = ChessboardTools::createEmptyBoard();

    std::vector<std::vector<Field> > board;
    std::vector<Field> row;
    auto letter{'A'};
    auto number{8};

    for (char it : boardString)
    {
        switch (it)
        {
        /********** white figures **********/
        case 'P':
        { // pawn
            Figure figure{"P_W", true};
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'R':
        { // rook
            Figure figure("R_W", true);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'N':
        { // knight
            Figure figure("N_W", true);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'B':
        { // bishop
            Figure figure("B_W", true);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'K':
        { // king
            Figure figure("K_W", true);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'Q':
        { // queen
            Figure figure("Q_W", true);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
            /********** black figures ***********/
        case 'p':
        { // pawn
            Figure figure("P_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'r':
        { // rook
            Figure figure("R_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'n':
        { // knight
            Figure figure("N_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'b':
        { // bishop
            Figure figure("B_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'k':
        { // king
            Figure figure("K_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
        case 'q':
        { // queen
            Figure figure("Q_B", false);
            Field field{letter, number};
            chessboard.addFigureOnField(figure, field);
            ++letter;
            break;
        }
            /********** further **********/
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        { // empty
            // TODO umschreiben, da ich hier nichts machen muss
            int c = (int)(it - '0'); // get value of char '1' . 1
            for (int i = 0; i < c; ++i)
            {
                Field field{letter, number}; // empty field
                ++letter;
            }
            break;
        }
        case '/':
        { //new row
            letter = 'A';
            --number;
            break;
        }
        default:
            break;
        }
    }
    return chessboard;
}

int mainChessboard()
{
    ChessBoard board = ChessboardTools::createStartingBoard();
    board.drawBoard();

    bool finished = false;
    int option;

    do
    {
        std::cout << "------ Menu ------\n"
                     "[1] draw current board \n"
                     "[2] get possible moves \n"
                     "[3] move figure \n"
                     "[4] print string for engine from board \n"
                     "[5] print board from string \n"
                     "[0] exit \n\n";

        std::cout << "Input: ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option)
        {
        case 1:
        { // draw current board
            board.drawBoard();
            break;
        }
        case 2:
        { // get possible moves
            Field f = ChessboardTools::selectField(board);
            std::cout << "selected Field: " << f.getLetter() << " " << f.getNumber() << std::endl;

            std::vector<Field> possMoves = board.getMoves(f);
            if (!possMoves.empty())
                std::cout << f.getFigure().getName() << " can move to " << std::endl;
            for (auto &possMove : possMoves)
            {
                std::cout << possMove.getLetter() << " " << possMove.getNumber() << "; ";
            }
            std::cout << std::endl
                      << std::endl;
            break;
        }
        case 3:
        { // move figure
            std::cout << "Select figure by entering field: " << std::endl;
            Field &oldField = ChessboardTools::selectField(board);
            if (oldField.getEmpty())
            {
                std::cout << "Field is empty" << std::endl;
                break;
            }
            // show possible moves for selected figure
            std::vector<Field> possMoves = board.getMoves(oldField);
            if (!possMoves.empty())
                std::cout << oldField.getFigure().getName() << " can move to " << std::endl;
            for (auto &possMove : possMoves)
            {
                std::cout << possMove.getLetter() << " " << possMove.getNumber() << "; ";
            }
            std::cout << "\n"
                      << std::endl;
            std::cout << "Enter field where to move figure: " << std::endl;
            Field &newField = ChessboardTools::selectField(board);
            board.moveFigure(oldField.getFigure(), oldField, newField, possMoves);
            break;
        }
        case 4:
        { // print string for engine
            std::string s = ChessboardTools::chessboardToString(board.getBoard());
            std::cout << s << std::endl;
            break;
        }

        case 5:
        { // print board from string
            int puzzleIndex;
            std::cout << "Enter number to select puzzle \n";
            std::cin >> puzzleIndex;
            //                    std::string testBoard = "r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR";
            auto puzzle = Puzzles::getPuzzle(puzzleIndex);
            //                std::cout << "Puzzle: " << puzzle.puzzle << std::endl;
            auto newBoard = ChessboardTools::stringToChessboard(puzzle.puzzle);
            newBoard.drawBoard();
            break;
        }
        case 0:
        { // exit
            finished = true;
            break;
        }
        default:
        {
            std::cout << "Please enter a valid option!\n\n";
        }
        }
    } while (!finished);

    return 0;
}

// returns the corresponding field on which the
Field getFieldOfMarker(Marker m, ChessBoard board)
{
    for (auto number : {8, 7, 6, 5, 4, 3, 2, 1})
    {
        bool nextLine = false;
        for (auto letter : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'})
        {
            Field &field = board.getField(letter, number);
            // TODO if index is not found exception is thrown

            Field::cornerPoints result = field.getCorners();
            auto [x, y] = m.getMiddle();
            if (result.corner0.x >= x && result.corner1.x <= x &&
                result.corner0.y <= y && result.corner2.y >= y)
            {
                return field;
            }

            if (x > result.corner1.x)
            {
                break;
            }

            if (x > result.corner2.y)
            {
                nextLine = true;
                break;
            }
        }

        if (nextLine)
        {
            break;
        }
    }
    return Field{};
}