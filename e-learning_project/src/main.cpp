#include "../include/main.h"
#include "../include/calibration/Calibration.h"
#include <thread>
#include <mutex>
#include <optional>
#include "../include/drawing/RenderUtils.h"


/* Constants */
// => remember to set videoWidth and Height in DrawTools accordingly!
// Webcam/Video HD
int videoWidth = 1280;
int videoHeight = 720;
// Webcam/Video Full HD
//int videoWidth = 1920;
//int videoHeight = 1080;
const float fieldSize = 0.04; // edge length of chessboard field in meters
const std::string videoFile = "./e-learning_project/puzzle_videos/puzzle1.mp4";

cv::VideoCapture cap;

// For thread synchronisation
std::atomic<bool> running = true;
std::atomic<bool> newVideoStream = false;

void initVideoStream(cv::VideoCapture& cap) {
	newVideoStream = true;
	// Check if cap is already open
	if (cap.isOpened())
		cap.release();
	// Open Cam
	//==> uncomment this to use the cam: cap.open(0);
	// Set Webcam Frame Width and Height
	if (cap.isOpened())
	{
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	}
	// Try to open a video if no webcam was found
	if (cap.isOpened() == false) {
		std::cout << "No webcam found, using a video file" << std::endl;
		cap.open(videoFile);
		if (cap.isOpened() == false) {
			std::cout << "No video file found. Exiting." << std::endl;
			exit(0);
		}
	}
	newVideoStream = false;
}

// displays the console menu
void consoleMenu()
{
	std::cout << "I'm your helpful companion who will guide you through the program ;)\n";
	std::cout << "1. Puzzle Mode\n";
	std::cout << "2. Show Valid Moves\n";
	std::cout << "3. Reset\n";
	std::cout << "Type \"exit\" to leave\n";
}

int main(int argc, char* argv[])
{
	// Setup OpenCV
	cv::Mat img_bgr;
	// Get video stream
	initVideoStream(cap);
	// initialize the chessboard with starting configuration
	auto chessBoard = ChessboardTools::createStartingBoard();
	// calibrate the chessboard, scans for the 4 edge markers 
	calib::calibrate(cap, chessBoard, fieldSize, videoWidth, videoHeight, false);
	// start open gl draw thread and chessboard calibration thread for realtime video display and calibration
	auto& drawThread = dtools::startDrawing(cap, chessBoard, videoWidth, videoHeight);
	auto& calibThread = calib::startCalibration(cap, chessBoard, fieldSize, videoWidth, videoHeight);
	// Loop until the user closes the window
	while (running)
	{
		//Get the current image from the openGL thread.
		consoleMenu();
		std::cout << "Input: ";
		string consoleInput;
		std::cin >> consoleInput;
		// Puzzle Mode
		if (consoleInput == "1")
		{
			// load the puzzle
			cout << "Select Puzzle (1-10): ";
			bool abort = GL_FALSE;
			int puzzleIndex;
			std::cin >> puzzleIndex;
			auto puzzle = Puzzles::getPuzzle(puzzleIndex);
			if (puzzle.puzzle.empty())
			{
				cout << "Can't find puzzle\n";
				continue;
			}
			bool found = false;
			Figure fig;
			std::optional<Field> oldField;
			std::optional<Field> newField;
			std::optional<Figure> oldFigure;
			bool newFigure = false;
			do
			{
				RenderUtils::clear();
				RenderUtils::setMove(puzzle.lastMoveOfOpponent);
				chessBoard.copyFigures(ChessboardTools::stringToChessboard(puzzle.puzzle));
				do
				{
					if (oldField.has_value())
					{
						fig = oldField.value().getFigure();
						fig.draw = false;
						chessBoard.getField(oldField.value().getLetter(), oldField.value().getNumber()).setFigure(fig);
					}
					cout << "Place any marker on the figure you want to play\n";
					cout << "Confirm (y): ";
					std::cin >> consoleInput;
					if (consoleInput == "exit")
					{
						running = false;
						break;
					}
					if (consoleInput == "abort")
					{
						abort = true;
						break;
					}
					cap.retrieve(img_bgr);
					// select figure with marker
					oldField = calib::calibrateMarkerToFigure(chessBoard, img_bgr);
					// check if there is a figure on the selected field
					if (oldField && !oldField.value().getFigure().name.empty())
					{
						fig = oldField.value().getFigure();
						fig.draw = true;
						chessBoard.getField(oldField.value().getLetter(), oldField.value().getNumber()).setFigure(fig);
						found = true;
					}
				} while (!found);
				if (!running || abort)
				{
					break;
				}
				std::vector<Field> possMoves;
				newFigure = false;
				do
				{
					found = false;
					cout << "Move your marker to the position you want to move your figure to\n";
					cout << "Confirm (y): ";
					std::cin >> consoleInput;
					if (consoleInput == "exit")
					{
						running = false;
						break;
					}
					if (consoleInput == "abort")
					{
						abort = true;
						break;
					}
					cap.retrieve(img_bgr);
					// find position where the selected figure should move to
					newField = calib::calibrateMarkerToFigure(chessBoard, img_bgr);
					// check if the desired move is valid
					if (newField)
					{
						// show possible moves for selected figure
						possMoves = chessBoard.getMoves(oldField.value());
						if (!newField.value().getEmpty())
							oldFigure = newField.value().getFigure();
						found = chessBoard.moveFigure(oldField.value().getFigure(), oldField.value(), newField.value(), possMoves);
						if (!found)
						{
							cout << "Invalid Move!\n";
							cout << "Do you want to try again? (y)\nSelect a new figure?(n): ";
							cin >> consoleInput;
							if (consoleInput == "n")
								newFigure = true;
						}
						else
						{
							chessBoard.getField(newField.value().getLetter(), newField.value().getNumber()).setFigure(oldField.value().getFigure());
							chessBoard.getField(oldField.value().getLetter(), oldField.value().getNumber()).setFigure(newField.value().getFigure());
							chessBoard.getField(oldField.value().getLetter(), oldField.value().getNumber()).setEmpty(true);
						}
					}
				} while (!found && !newFigure);
				// confirmation if the move should be done and execute the move
				if (!newFigure)
				{
					if (!running)
						break;
					cout << "Confirm your move? (y/n): ";
					cin >> consoleInput;
					if (consoleInput != "y")
					{
						possMoves = chessBoard.getMoves(newField.value());
						chessBoard.moveFigure(newField.value().getFigure(), newField.value(), oldField.value(), possMoves);
					}
				}
				if (consoleInput == "abort")
				{
					abort = true;
					break;
				}
			} while (newFigure || consoleInput != "y");
			if (!running)
				break;
			if (abort)
				continue;
			// display message if puzzle was solved correctly or not
			if (oldField.value().getLetter() == puzzle.solution.from.getLetter() && oldField.value().getNumber() == puzzle.solution.from.getNumber()
				&& newField.value().getLetter() == puzzle.solution.to.getLetter() && newField.value().getNumber() == puzzle.solution.to.getNumber())
				cout << "Congratulations! GG! Well done! Have fun with the next puzzle.\n\n";
			else
			{
				cout << "That was not correct. Think about your move again!\n";
				cout << "Do you want to see the solution? (y|n)\n";
				cout << "Input: ";
				cin >> consoleInput;
				if (consoleInput == "y")
					RenderUtils::setMove(puzzle.solution);
			}
		}
		// Valid Move Mode
		else if (consoleInput == "2")
		{
			// Clear drawing if present
			RenderUtils::clear();
			// removes all figures from the chessboard
			chessBoard.clear();
			// find marker representing a figure on the chessboard
			cap.retrieve(img_bgr);
			auto markers = md::findMarkerInFrame(img_bgr);

			for (auto& m : markers)
			{
				// check for white figures (black would be analogous)
				// important: drawing of figure set to true
				if (m.getID() == 0x22fa) // King
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "K_W",true, true }, field.value());
				}
				else if (m.getID() == 0x1C32) // Queen
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "Q_W",true , true }, field.value());
				}
				else if (m.getID() == 0x0f88) // Knight
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "N_W",true , true }, field.value());
				}
				else if (m.getID() == 0xFF2) // Rook
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "R_W",true , true }, field.value());
				}
				else if (m.getID() == 0x05A1) // Pawn
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "P_W",true, true }, field.value());
				}
				else if (m.getID() == 0x1249) // Bishop
				{
					auto field = chessBoard.locateField(m.getMiddle());
					if (field.has_value())
						chessBoard.addFigureOnField({ "B_W",true , true }, field.value());
				}
			}

		}
		// Clear the board and load the starting configuration
		else if (consoleInput == "3")
		{
			RenderUtils::clear();
			chessBoard.copyFigures(ChessboardTools::createStartingBoard());
		}
		else if (consoleInput == "exit")
		{
			running = false;
			break;
		}
	}
	calib::endCalibration(calibThread);
	dtools::stopDrawing(drawThread);
	return 0;
}