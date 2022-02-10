# E-Learning Project: AR Chess

## Project Structure
- e-learning_project contains the C++ Project
    - all source files etc. are added there
    - videos are included there
    - 3D models are included there (but not used yet!)
- figure markers are added in directory "figure_markers"
- if you want to have the video you need to have git lfs

### Dependencies
- OpenCV 3.14.4
- OpenGL 2.1
- GLEW 2.1.0
- GLFW 3.3.4

### Contributors
- Jonas Bauer (ge38cuy@mytum.de)
- Franziska Buck (franziska.buck@tum.de)
- Felix Moser (f.moser@tum.de)
- Alexander Partsch (alexander.partsch@tum.de)
- Laura Xourgias (ge49yos@mytum.de) <br><br>
* * * * * * * * * * * * * * * * * * * * * * * *

## Project Goal
The goal of this project is to introduce newbies to chess with the help of an interactive marker-based augmented e-learning application.<br> 
To support a high learning curve, the application is divided into a training mode and a puzzle mode <br>
In training mode, the user can learn about the different moves a figure is allowed to do, meanwhile puzzle mode provides the user with various chess riddles in which they can apply their aquired knowledge.<br><br> 
* * * * * * * * * * * * * * * * * * * * * * * *
## Implementation

### 1. Setup
To set up the application, the user has to place the four chessboard markers in the corners of their chessboard.
In training mode, the user can use markers to select a figure in order to get all possible moves displayed, meanwhile the marker acts as a selector during puzzle mode. This way, the user can select their chosen figure and perform their prefered move. At startup the user gets displayed a console window into which they can enter their inputs. In the general menu, it is possible to choose between showing all valid moves, aka "Training mode", as well as puzzle mode. It also includes the possiblity to reset the chessboard to its original state. Entering "exit" will shut down the program.

### 2. Training Mode
During training mode, the user can place specific markers on the chessboard and is provided with all possible moves of the chosen figure directly on the board. This allows the user to learn about which moves a specific figure is allowed to make.


The user can use the slider in the application window to select and preview a chess riddle he or she wants to practice on. Putting a marker on a field on which a chess figure is displayed and pressing the available button connects the marker to a figure. The application then shows all available moves for this figure. After moving the figure and pressing the button again, the system evaluates the validity of the move and checks if the chess puzzle was solved correctly with it.

### 3. Puzzle Mode
After selecting Puzzle Mode, the user can choose between 10 different puzzles, which can be selected by entering the respective number. Afterwards, the chosen puzzle will be loaded onto the board and the user can place the selector-marker on its chosen field in order to log in the respective figure on it. Next, the user can place the selector on the field where the figure needs to be moved and confirm the move via the console. The program then gives the user feedback about its move and also offers help, if necessary.
<br><br>
* * * * * * * * * * * * * * * * * * * * * * * *
## Outlook
The following list contains ideas of the project team to expand the application's functionality (was not possible in scope of this project): <br>

### 1. General Ideas to improve AR experience
- optimize User Interface using GUI elements
- provide interface for HMDs
- use shadows, textures, lighting and load externally designed 3D modeled chess figures
- detect hands to select chess figures

### 2. Training Mode
- include marker tracking to show OpenGL drawn chess figure on top of the marker while moving it

### 3. Game Mode
- enable prospective game play by providing possibility to select one figure to show possible moves
- implement of chess engine to recommend most suitable next move for user

* * * * * * * * * * * * * * * * * * * * * * * *

