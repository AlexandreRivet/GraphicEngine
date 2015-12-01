#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Math/Vector2.h"
#include "Structs.h"

void drawPoint(Vector2 point, Color color);
void drawLine(Vector2 start, Vector2 end, Color color, int thickness, int dashed = -1);
void drawLines(std::vector<Vector2*> points, Color color, int thickness, bool close = true);
void drawLines(std::vector<Vector2> points, Color color, int thickness, bool close = true);
void drawSquareCentered(Vector2 point, int w, int h, Color fill, Color stroke);
void drawSquare(Vector2 point, int w, int h, Color fill, Color stroke);
void drawPolygon(std::vector<Vector2> points, Color fill, Color stroke);
void drawString(std::string label, Vector2 point, Color color);
void drawStringCentered(std::string label, Vector2 point, Vector2 rect, Color color, bool centeredOnX, bool centeredOnY);
void drawCircle(Vector2 center, float radius, Color color, float step = 1.0f);

int getXCoordInString(std::string label, Vector2 origin, int posChar);
int getSizeBetweenTwoPosInString(std::string label, int start = 0, int end = -1);
int getPosInString(std::string label, int x_start, int x_current);

#endif