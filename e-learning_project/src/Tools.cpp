#include "../include/Tools.h"
#include <iostream>
#include "../include/markerdetection/PoseEstimation.h"

Mat calculate_Stripe(double dx, double dy, MyStrip& st) {
    // Norm (euclidean distance) from the direction vector is the length (derived from the Pythagoras Theorem)
    double diffLength = sqrt(dx * dx + dy * dy);

    // Length proportional to the marker size
    st.stripeLength = (int)(0.8 * diffLength);

    if (st.stripeLength < 5)
        st.stripeLength = 5;

    // Make stripeLength odd (because of the shift in nStop), Example 6: both sides of the strip must have the same length XXXOXXX
    st.stripeLength |= 1;
    /*if (st.stripeLength % 2 == 0)
        st.stripeLength++;*/

    // E.g. stripeLength = 5 --> from -2 to 2: Shift -> half top, the other half bottom
    st.nStop = st.stripeLength >> 1;
    //st.nStop = st.stripeLength / 2;
    st.nStart = -st.nStop;

    Size stripeSize;

    // Sample a strip of width 3 pixels
    stripeSize.width = 3;
    stripeSize.height = st.stripeLength;

    // Normalized direction vector
    st.stripeVecX.x = dx / diffLength;
    st.stripeVecX.y = dy / diffLength;

    // Normalized perpendicular vector
    st.stripeVecY.x = st.stripeVecX.y;
    st.stripeVecY.y = -st.stripeVecX.x;

    // 8 bit unsigned char with 1 channel, gray
    return Mat(stripeSize, CV_8UC1);
}

int subpixSampleSafe(const Mat& pSrc, const Point2f& p) {
    // Point is float, slide 14
    int fx = int(floorf(p.x));
    int fy = int(floorf(p.y));

    if (fx < 0 || fx >= pSrc.cols - 1 ||
        fy < 0 || fy >= pSrc.rows - 1)
        return 127;

    // Slides 15
    int px = int(256 * (p.x - floorf(p.x)));
    int py = int(256 * (p.y - floorf(p.y)));

    // Here we get the pixel of the starting point
    unsigned char* i = (unsigned char*)((pSrc.data + fy * pSrc.step) + fx);

    // Internsity, shift 3
    int a = i[0] + ((px * (i[1] - i[0])) >> 8);
    i += pSrc.step;
    int b = i[0] + ((px * (i[1] - i[0])) >> 8);

    // We want to return Intensity for the subpixel
    return a + ((py * (b - a)) >> 8);
}

contour_vector_t filterContours(Mat& image, Mat drawImage)
{
    // initial raw contours
    contour_vector_t contours;
    // return value containing all suitable contours found in the image
    contour_vector_t processedContours;
    // RETR_LIST is a list of all found contour, SIMPLE is to just save the begin and ending of each edge which belongs to the contour
    findContours(image, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Filter contours
    for (size_t k = 0; k < contours.size(); k++) {
        contour_t approx_contour;
        // Simplifying of the contour with the Ramer-Douglas-Peuker Algorithm
        // true -> Only closed contours
        // Approximation of old curve, the difference (epsilon) should not be bigger than: perimeter(->arcLength)*0.02
        approxPolyDP(contours[k], approx_contour, arcLength(contours[k], true) * 0.02, true);

        // Convert to a usable rectangle
        Rect r = boundingRect(approx_contour);

        // 4 Corners -> We color them
        if (approx_contour.size() != 4) {
            continue;
        }
        // --- Filter tiny ones --- If the found contour is too small (20 -> pixels, frame.cols - 10 to prevent extreme big contours)
        // TODO: determine best filter criteria
        if (r.height < 30 || r.width < 30 || r.width > image.cols / 4 || r.height > image.rows / 4) {
            continue;
        }

        processedContours.push_back(approx_contour);
    }
    return processedContours;
}

contour_vector_f improveContourEdges(Mat& image, Mat& grayScale, contour_vector_t contours)
{
    contour_vector_f improvedContours;
    for (size_t outer = 0; outer < contours.size(); outer++) {
        /**
        * #####################################################################
        * ### Variables needed per contour (per marker)
        * #####################################################################
        */
        // newly calculated intersection points that replace points in contours
        contour_f intersectionPoints;
        // parameters of the four lines of a single contour
        float lineParams[16];
        // line parameters saved to Mat
        Mat lineParamsMat(cv::Size(4, 4), CV_32F, lineParams);
        for (size_t i = 0; i < contours[outer].size(); ++i) {
            // Euclidic distance, 7 -> parts, both directions dx and dy
            double dx = ((double)contours[outer][(i + 1) % 4].x - (double)contours[outer][i].x) / 7.0;
            double dy = ((double)contours[outer][(i + 1) % 4].y - (double)contours[outer][i].y) / 7.0;
            // Calculate Stripe Size
            double normLength = sqrt(dx * dx + dy * dy);
            int stripeLength = (int)(0.8 * normLength);
            if (stripeLength < 5) // make sure stripe is not too short
                stripeLength = 5;
            if (stripeLength % 2 == 0) // make sure stripe is symmetrical wrt to center
                stripeLength++;
            MyStrip strip;

            // A simple array of unsigned char cv::Mat
            Mat imagePixelStripe = calculate_Stripe(dx, dy, strip);

            // Array for edge point centers
            Point2f edgePointCenters[6];

            // First point already rendered, now the other 6 points
            for (int j = 1; j < 7; ++j) {
                // Position calculation
                double px = (double)contours[outer][i].x + (double)j * dx;
                double py = (double)contours[outer][i].y + (double)j * dy;

                Point p;
                p.x = (int)px;
                p.y = (int)py;

                // Columns: Loop over 3 pixels
                for (int m = -1; m <= 1; ++m) {
                    // Rows: From bottom to top of the stripe, e.g. -3 to 3
                    for (int n = strip.nStart; n <= strip.nStop; ++n) {
                        Point2f subPixel;

                        // m -> going over the 3 pixel thickness of the stripe, n -> over the length of the stripe, direction comes from the orthogonal vector in st
                        // Going from bottom to top and defining the pixel coordinate for each pixel belonging to the stripe
                        subPixel.x = (double)p.x + ((double)m * strip.stripeVecX.x) + ((double)n * strip.stripeVecY.x);
                        subPixel.y = (double)p.y + ((double)m * strip.stripeVecX.y) + ((double)n * strip.stripeVecY.y);

                        Point p2;
                        p2.x = (int)subPixel.x;
                        p2.y = (int)subPixel.y;

                        // Combined Intensity of the subpixel
                        int pixelIntensity = subpixSampleSafe(grayScale, subPixel);

                        // Converte from index to pixel coordinate
                        // m (Column, real) -> -1,0,1 but we need to map to 0,1,2 -> add 1 to 0..2
                        int w = m + 1;

                        // n (Row, real) -> add stripeLenght >> 1 to shift to 0..stripeLength
                        // n=0 -> -length/2, n=length/2 -> 0 ........ + length/2
                        int h = n + (strip.stripeLength >> 1);

                        // Set pointer to correct position and safe subpixel intensity
                        imagePixelStripe.at<uchar>(h, w) = (uchar)pixelIntensity;
                    }
                }
                // Use sobel operator on stripe

                // ( -1 , -2, -1 )
                // (  0 ,  0,  0 )
                // (  1 ,  2,  1 )

                // The first and last row must be excluded from the sobel calculation because they have no top or bottom neighbors
                vector<double> sobelValues(strip.stripeLength - 2.);

                // To use the kernel we start with the second row (n) and stop before the last one
                for (int n = 1; n < (strip.stripeLength - 1); n++) {
                    // Take the intensity value from the stripe
                    unsigned char* stripePtr = &(imagePixelStripe.at<uchar>(n - 1, 0));

                    // Calculation of the gradient with the sobel for the first row
                    double r1 = -stripePtr[0] - 2. * stripePtr[1] - stripePtr[2];

                    // r2 -> Is equal to 0 because of sobel

                    // Go two lines for the third line of the sobel, step = size of the data type, here uchar
                    stripePtr += 2 * imagePixelStripe.step;

                    // Calculation of the gradient with the sobel for the third row
                    double r3 = stripePtr[0] + 2. * stripePtr[1] + stripePtr[2];

                    // Writing the result into our sobel value vector
                    unsigned int ti = n - 1;
                    sobelValues[ti] = r1 + r3;
                }
                // find the exact edge and improve the point p
                double maxIntensity = -1;
                int maxIntensityIndex = 0;

                // Finding the max value
                for (int n = 0; n < strip.stripeLength - 2; ++n) {
                    if (sobelValues[n] > maxIntensity) {
                        maxIntensity = sobelValues[n];
                        maxIntensityIndex = n;
                    }
                }
                //point before and after
                double y0, y1, y2;

                unsigned int max1 = maxIntensityIndex - 1;
                unsigned int max2 = maxIntensityIndex + 1;

                // If the index is at the border we are out of the stripe, then we will take 0
                y0 = (maxIntensityIndex <= 0) ? 0 : sobelValues[max1];
                y1 = sobelValues[maxIntensityIndex];
                // If we are going out of the array of the sobel values
                y2 = (maxIntensityIndex >= strip.stripeLength - 3) ? 0 : sobelValues[max2];

                // Formula for calculating the x-coordinate of the vertex of a parabola, given 3 points with equal distances
                // (xv means the x value of the vertex, d the distance between the points):
                // xv = x1 + (d / 2) * (y2 - y0)/(2*y1 - y0 - y2)

                // Equation system
                // d = 1 because of the normalization and x1 will be added later
                double pos = (y2 - y0) / (4 * y1 - 2 * y0 - 2 * y2);

                // What happens when there is no solution? -> /0 or Number = other Number
                // If the found pos is not a number -> there is no solution
                if (isnan(pos)) {
                    continue;
                }
                // Exact point with subpixel accuracy
                Point2d edgeCenter;
                // Back to Index positioning, Where is the edge (max gradient) in the picture?
                int maxIndexShift = maxIntensityIndex - (strip.stripeLength >> 1);

                // Shift the original edgepoint accordingly -> Is the pixel point at the top or bottom?
                edgeCenter.x = (double)p.x + (((double)maxIndexShift + pos) * strip.stripeVecY.x);
                edgeCenter.y = (double)p.y + (((double)maxIndexShift + pos) * strip.stripeVecY.y);

                edgePointCenters[j - 1].x = edgeCenter.x;
                edgePointCenters[j - 1].y = edgeCenter.y;
            } // ------ end of inner points processing --------
            // Matrix with the improved helper points
            Mat point_mat(cv::Size(1, 6), CV_32FC2, edgePointCenters);
            // fit of new line through the improved points
            fitLine(point_mat, lineParamsMat.col(i), CV_DIST_L2, 0, 0.01, 0.01);
        } // -------- end of processing of single contour --------
        // So far we stored the exact line parameters and show the lines in the image now we have to calculate the exact corners
        Point2f corners[4];

        // Calculate the intersection points of both lines
        for (int i = 0; i < 4; ++i) {
            // Go through the corners of the rectangle, 3 -> 0
            int j = (i + 1) % 4;

            double x0, x1, y0, y1, u0, u1, v0, v1;

            // We have to jump through the 4x4 matrix, meaning the next value for the wanted line is in the next row -> +4
            // g: Point + d*Vector
            // g1 = (x0,y0) + scalar0*(u0,v0) == g2 = (x1,y1) + scalar1*(u1,v1)
            x0 = lineParams[i + 8]; y0 = lineParams[i + 12];
            x1 = lineParams[j + 8]; y1 = lineParams[j + 12];

            // Direction vector
            u0 = lineParams[i]; v0 = lineParams[i + 4];
            u1 = lineParams[j]; v1 = lineParams[j + 4];
            // Cramer's rule
            // 2 unknown a,b -> Equation system
            double a = x1 * u0 * v1 - y1 * u0 * u1 - x0 * u1 * v0 + y0 * u0 * u1;
            double b = -x0 * v0 * v1 + y0 * u0 * v1 + x1 * v0 * v1 - y1 * v0 * u1;

            // Calculate the cross product to check if both direction vectors are parallel -> = 0
            // c -> Determinant = 0 -> linear dependent -> the direction vectors are parallel -> No division with 0
            double c = v1 * u0 - v0 * u1;
            if (fabs(c) < 0.001) {
                continue;
            }

            // We have checked for parallelism of the direction vectors
            // -> Cramer's rule, now divide through the main determinant
            a /= c;
            b /= c;

            // Exact corner
            corners[i].x = a;
            corners[i].y = b;

            intersectionPoints.push_back(corners[i]);
        } // End of the loop to extract the exact corners
        // Highlight the corrected intersection points and connect them with lines

        if (intersectionPoints.size() == 4)
        {
            // save the new corners of the contour to a vector containing all corrected contours
            improvedContours.push_back(intersectionPoints);
        }
    } // -------- end of processing of all contours --------
    return improvedContours;
}

vector<tuple<Mat, contour_f>> extractValidMarkers(Mat& grayScale, contour_vector_f contours, int slider_value)
{
    vector<tuple<Mat, contour_f>> markers;
    for (size_t i = 0; i < contours.size(); i++) {
        Point2f contour[4];
        if (contours[i].size() != 4)
            continue;
        for (int j = 0; j < 4; j++) {
            contour[j] = contours[i][j];
        }

        // calculate transformation matrix to undo the perspective image
        // define the image corners to map the marker onto
        static const Point2f dst[4] = {
                Point2f(-0.5, -0.5),
                Point2f(5.5, -0.5),
                Point2f(5.5, 5.5),
                Point2f(-0.5, 5.5)
        };
        // Create and calculate the matrix of perspective transform -> non affin -> parallel stays not parallel
        // Homography is a matrix to describe the transformation from an image region to the 2D projected image
        Mat homographyMatrix(Size(3, 3), CV_32FC1);
        // Corner which we calculated and our target Mat, find the transformation
        homographyMatrix = getPerspectiveTransform(contour, dst);

        // Create image for the marker
        Mat imageMarker(Size(6, 6), CV_8UC1);

        // Change the perspective in the marker image using the previously calculated Homography Matrix
        // In the Homography Matrix there is also the position in the image saved
        warpPerspective(grayScale, imageMarker, homographyMatrix, Size(6, 6));
        // Now we have a B/W image of a supposed Marker
        //cv::cvtColor(imageMarker, imageMarker, COLOR_BGR2GRAY);
        threshold(imageMarker, imageMarker, 150, 255, CV_THRESH_BINARY);

        int code = 0;
        for (int i = 0; i < 6; ++i) {
            // Check if border is black
            int pixel1 = imageMarker.at<uchar>(0, i); //top
            int pixel2 = imageMarker.at<uchar>(5, i); //bottom
            int pixel3 = imageMarker.at<uchar>(i, 0); //left
            int pixel4 = imageMarker.at<uchar>(i, 5); //right

            // 0 -> black
            if ((pixel1 > 0) || (pixel2 > 0) || (pixel3 > 0) || (pixel4 > 0)) {
                code = -1;
                break;
            }
        }

        if (code < 0) {
            continue;
        }
        markers.emplace_back(imageMarker, contours[i]);
    }
    return markers;
}

vector<Marker> extractMarkers(vector<tuple<Mat, contour_f>> markers)
{
    vector<Marker> extractedMarkers;
    for (size_t i = 0; i < markers.size(); i++)
    {
        Mat markerImage = std::get<0>(markers[i]);
        // Copy the BW values into cP -> codePixel on the marker 4x4 (inner part of the marker, no black border)
        int cP[4][4];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                // +1 -> no borders!
                cP[i][j] = markerImage.at<uchar>(i + 1, j + 1);
                // If black then 1 else 0
                cP[i][j] = (cP[i][j] == 0) ? 1 : 0;
            }
        }
        // Save the ID of the marker, for each side
        int codes[4];
        codes[0] = codes[1] = codes[2] = codes[3] = 0;
        // Calculate the code from all sides at once
        for (int i = 0; i < 16; i++) {
            // /4 to go through the rows
            int row = i >> 2;
            int col = i % 4;

            // Multiplied by 2 to check for black values -> 0*2 = 0
            codes[0] <<= 1;
            codes[0] |= cP[row][col]; // 0

            // 4x4 structure -> Each column represents one side
            codes[1] <<= 1;
            codes[1] |= cP[3 - col][row]; // 90

            codes[2] <<= 1;
            codes[2] |= cP[3 - row][3 - col]; // 180

            codes[3] <<= 1;
            codes[3] |= cP[col][3 - row]; // 270
        }
        // Account for symmetry -> One side complete white or black
        if ((codes[0] == 0) || (codes[0] == 0xffff)) {
            continue;
        }
        // Search for the smallest marker ID
        int code = codes[0];
        int orientation = 0;
        for (int i = 1; i < 4; ++i) {
            if (codes[i] < code) {
                code = codes[i];
                orientation = i;
            }
        }
        extractedMarkers.emplace_back(code, orientation, std::get<1>(markers[i]));
    }
    return extractedMarkers;
}