#include "../../include/main.h"
#include <thread>
#include "../../include/drawing/RenderUtils.h"
#include <atomic>
const int camera_width = 1280;
const int camera_height = 720;
// Webcam
//const int camera_width = 1920;
//const int camera_height = 1080;
unsigned char bkgnd[camera_width * camera_height * 3];

/**
 * <br/> This function is copied from the example solution.
 * @param argc
 * @param argv
 */
void dtools::initGL()
{
	// For our connection between OpenCV/OpenGL
	// Pixel storage/packing stuff -> how to handle the pixel on the graphics card
	// For glReadPixels​ -> Pixel representation in the frame buffer
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	// For glTexImage2D​ -> Define the texture image representation
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Turn the texture coordinates from OpenCV to the texture coordinates OpenGL
	glPixelZoom(1.0, -1.0);

	// Enable and set colors
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 0, 1.0);

	// Enable and set depth parameters
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	// Light parameters
	GLfloat light_amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_dif[] = { 0.7, 0.7, 0.7, 1.0 };

	// Enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

/**
 * <br/> This function is copied from the example solution.
 */
void dtools::display(GLFWwindow* window, const cv::Mat& img_bgr, int camera_width, int camera_height)
{

	// Copy picture data into bkgnd array
	memcpy(bkgnd, img_bgr.data, sizeof(bkgnd));

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Needed for rendering the real camera image
	glMatrixMode(GL_MODELVIEW);
	// No position changes
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	// Push the projection matrix (frustum) -> frustum will be saved on the stack
	glPushMatrix();
	glLoadIdentity();
	// In the ortho view all objects stay the same size at every distance
	glOrtho(0.0, camera_width, 0.0, camera_height, -1, 1);

	// -> Render the camera picture as background texture
	// Making a raster of the image -> -1 otherwise overflow
	glRasterPos2i(0, camera_height - 1);
	// Load and render the camera image -> unsigned byte because of bkgnd as unsigned char array
	// bkgnd 3 channels -> pixelwise rendering
	glDrawPixels(camera_width, camera_height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bkgnd);;

	// Go back to the previous projection -> frustum
	glPopMatrix();

	// Activate depth -> that snowman can be scaled with depth
	glEnable(GL_DEPTH_TEST);

	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
}

/**
 * <br/> This function is copied from the example solution.
 */
void dtools::reshape(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Create a perspective projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// The camera should be calibrated -> a calibration results in the projection matrix -> then load the matrix
	// -> into GL_PROJECTION
	// -> adjustment of FOV is needed for each camera
	float ratio = (GLfloat)width / (GLfloat)height;

	float near = 0.01f, far = 100.f;
	float top = tan((double)(camera_angle * M_PI / 360.0f)) * near;
	float bottom = -top;
	float left = ratio * bottom;
	float right = ratio * top;
	glFrustum(left, right, bottom, top, near, far);
}

/**
 * <br/> colorize a specific field on the board.
 * @param tm needs to be an opencv transpose matrix
 */
void dtools::colorField(std::array<float, 16> tm)
{
	std::array<float, 16> resultTransposedMatrix;

	//glLoadMatrixf(resultTransposedMatrix);
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			// Change columns to rows
			resultTransposedMatrix[x * 4 + y] = tm[y * 4 + x];
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(resultTransposedMatrix.data());
	glScalef(0.03, 0.03, 0.03);
	glRotatef(180, 1, 0, 0);
	glColor4f(1.0, 0, 0, 1);
	drawFilledCircle(0.3);
	glPopMatrix();
}

/**
 * <br/> This function draws a cube.
 * TODO: don't work perfect!
 */
void dtools::drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
	GLfloat halfSideLength = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// back face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

		// left face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// right face
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

		// top face
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
	};

	//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//glColor3f( colour[0], colour[1], colour[2] );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void dtools::drawFilledCircle(GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			(radius * cos(i * twicePi / triangleAmount)),
			(radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

/**
 * <br/> This function is copied from the example solution.
 */
void dtools::drawCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
	// draw the upper part of the cone
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, height);
	for (int angle = 0; angle < 360; ++angle) {
		glVertex3f(sin((double)angle) * base, cos((double)angle) * base, 0.f);
	}
	glEnd();

	// draw the base of the cone
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int angle = 0; angle < 360; ++angle) {
		// normal is just pointing down
		glNormal3f(0, -1, 0);
		glVertex3f(sin((double)angle) * base, cos((double)angle) * base, 0.f);
	}
	glEnd();
}

/**
 * <br/> This function is copied from the example solution.
 */
void dtools::drawSphere(double r, int lats, int longs) {
	int i, j;
	for (i = 0; i <= lats; ++i) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = r * sin(lat0);
		double zr0 = r * cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = r * sin(lat1);
		double zr1 = r * cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; ++j) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}


void dtools::drawSquare(float edgeLength)
{
	glColor4f(0, 1, 0, 0.0);
	// draw a filled polygon
	glBegin(GL_POLYGON);
	glVertex3f(-(edgeLength / 2), -(edgeLength / 2), 0);
	glVertex3f((edgeLength / 2), -(edgeLength / 2), 0);
	glVertex3f((edgeLength / 2), (edgeLength / 2), 0);
	glVertex3f(-(edgeLength / 2), (edgeLength / 2), 0);
	glEnd();
}

/**
 * <br/> if a figure is selected all possible moves of it will displayed
 */
void dtools::selectField(Field& field, ChessBoard& chessboard)
{
	for (auto& f : chessboard.getMoves(field))
	{
		colorField(f.transformationMatrix);
	}
}
/**
 * <br/> Draw a specific figure on a specific position.
 * @param tm needs to be an opencv transpose matrix
 */
void dtools::drawFigure(Figure figure, std::array<float, 16> tm)
{
	std::array<float, 16> resultTransposedMatrix;

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			// Change columns to rows
			resultTransposedMatrix[x * 4 + y] = tm[y * 4 + x];
		}
	}

	std::string name = figure.getName();
	if (name == "K_W")
	{
		DrawFigures::drawKingWhite(resultTransposedMatrix);
	}
	else if (name == "Q_W")
	{
		DrawFigures::drawQueenWhite(resultTransposedMatrix);
	}
	else if (name == "B_W")
	{
		DrawFigures::drawBishop(resultTransposedMatrix);
	}
	else if (name == "N_W")
	{
		DrawFigures::drawKnightWhite(resultTransposedMatrix);
	}
	else if (name == "R_W")
	{
		DrawFigures::drawRookWhite(resultTransposedMatrix);
	}
	else if (name == "P_W")
	{
		DrawFigures::drawPawnWhite(resultTransposedMatrix);
	}
	else if (name == "K_B")
	{
		DrawFigures::drawKingBlack(resultTransposedMatrix);
	}
	else if (name == "Q_B")
	{
		DrawFigures::drawQueenBlack(resultTransposedMatrix);
	}
	else if (name == "B_B")
	{
		DrawFigures::drawBishopBlack(resultTransposedMatrix);
	}
	else if (name == "N_B")
	{
		DrawFigures::drawKnightBlack(resultTransposedMatrix);
	}
	else if (name == "R_B")
	{
		DrawFigures::drawRookBlack(resultTransposedMatrix);
	}
	else if (name == "P_B")
	{
		DrawFigures::drawPawnBlack(resultTransposedMatrix);
	}
}

/**
 * <br/> Draw all openGL figures over the marker or fields.
 */
void dtools::drawChessboard(ChessBoard& chessboard)
{
	for (auto row : chessboard.getBoard())
	{
		for (auto& f : row)
		{
			if (!f.getEmpty())
			{
				drawFigure(f.getFigure(), f.transformationMatrix);
				if (f.getFigure().shouldDraw())
					dtools::selectField(f, chessboard);
			}
		}
	}
}

/**
 * <br/> Draw the last move and the solution move of a puzzle.
 */
void dtools::drawMove(const Move& m, ChessBoard& board)
{
	if (m.figure.name.empty())
		return;
	auto tm = board.getField(m.from.getLetter(), m.from.getNumber()).transformationMatrix;
	std::array<float, 16> resultTransposedMatrix;

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			// Change columns to rows
			resultTransposedMatrix[x * 4 + y] = tm[y * 4 + x];
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(resultTransposedMatrix.data());
	glScalef(0.03, 0.03, 0.03);
	glRotatef(180, 1, 0, 0);
	glColor4f(0, 1, 0, 1);
	drawFilledCircle(0.4);
	glPopMatrix();
	tm = board.getField(m.to.getLetter(), m.to.getNumber()).transformationMatrix;
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			// Change columns to rows
			resultTransposedMatrix[x * 4 + y] = tm[y * 4 + x];
		}
	}
	glPushMatrix();
	glLoadMatrixf(resultTransposedMatrix.data());
	glScalef(0.03, 0.03, 0.03);
	glRotatef(180, 1, 0, 0);
	glColor4f(0, 1, 0, 1);
	drawFilledCircle(0.4);
	glPopMatrix();
}

extern std::atomic<bool> running;
void dtools::draw(cv::VideoCapture& cap, ChessBoard& chessboard, int videoWidth, int videoHeight)
{
	GLFWwindow* window;
	// Initialize the library
	if (!glfwInit())
		return;

	// Initialize the window system
	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(videoWidth, videoHeight, "AR Chess", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	// Set callback functions for GLFW
	glfwSetFramebufferSizeCallback(window, dtools::reshape);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int window_width, window_height;
	glfwGetFramebufferSize(window, &window_width, &window_height);
	dtools::reshape(window, window_width, window_height);

	// Initialize the GL library
	dtools::initGL();
	cv::Mat img_bgr;
	while (!glfwWindowShouldClose(window) && running) {
		// Capture here
		cap >> img_bgr;
		// Make sure that we got a frame -> otherwise crash
		if (img_bgr.empty()) {
			initVideoStream(cap);
			// Wait for one sec.
			//cv::waitKey(1000);
			continue;
		}
		// draw the opencv image on the screen
		dtools::display(window, img_bgr, videoWidth, videoHeight);
		// iterate all found marker and set the right figure on the internal chess board
		dtools::drawChessboard(chessboard);

		// Draw last move
		auto move = RenderUtils::getMove();
		if (move)
			dtools::drawMove(move.value(), chessboard);
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}
	running = false;
	glfwTerminate();
}

/**
 * <br/> Starts a thread that render all opengl stuff
 */
std::thread& dtools::startDrawing(cv::VideoCapture& cap, ChessBoard& chessboard, int videoWidth, int videoHeight)
{
	static std::thread drawing(dtools::draw, std::ref(cap), std::ref(chessboard), videoWidth, videoHeight);
	return drawing;
}

/**
 * <br/> Stop the drawing thread and waiting after the last loop will end.
 */
void dtools::stopDrawing(std::thread& t)
{
	running = false;
	t.join();
}