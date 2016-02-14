#include "UI/Shapes.h"

#include "Utils/freeglut_include.h"

#include "Utils/utils.h"

void drawPoint(Vector2 point, ColorStruct color)
{
	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_POINT);
	glVertex2f(point.x, point.y);
	glEnd();

	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
}

void drawLines(std::vector<Vector2*> points, ColorStruct color, int thickness, bool close)
{
	uint nbPoints = points.size();
	if (nbPoints < 2)
		return;

	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glLineWidth(static_cast<GLfloat>(thickness));

	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
	for (uint i = 0; i < nbPoints - 1; ++i)
	{
		glVertex2f(points[i]->x, points[i]->y);
		glVertex2f(points[i + 1]->x, points[i + 1]->y);
	}
	if (close)
	{
		glVertex2f(points[nbPoints - 1]->x, points[nbPoints - 1]->y);
		glVertex2f(points[0]->x, points[0]->y);
	}
	glEnd();

	glLineWidth(1);
	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
}

void drawLines(std::vector<Vector2> points, ColorStruct color, int thickness, bool close)
{
	uint nbPoints = points.size();
	if (nbPoints < 2)
		return;

	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glLineWidth(static_cast<GLfloat>(thickness));

	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
	for (uint i = 0; i < nbPoints - 1; ++i)
	{
		glVertex2f(points[i].x, points[i].y);
		glVertex2f(points[i + 1].x, points[i + 1].y);
	}
	if (close)
	{
		glVertex2f(points[nbPoints - 1].x, points[nbPoints - 1].y);
		glVertex2f(points[0].x, points[0].y);
	}
	glEnd();

	glLineWidth(1);
	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
}

void drawLine(Vector2 start, Vector2 end, ColorStruct color, int thickness, int dashed)
{
	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glLineWidth(static_cast<GLfloat>(thickness));

	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
	if (dashed > 0)
	{
		float distance = start.distance(end);
		int numberDash = distance / ((float)dashed * 2.0f);	// nombre de paires dash + dash vide
		Vector2 start_end = (end - start);
		Vector2 step;
		for (int i = 0; i < numberDash; ++i)
		{
			step = ((static_cast<float>(i) / static_cast<float>(numberDash)) * start_end);
			Vector2 new_start = step + start;
			step = (((static_cast<float>(i)* 2.0f + 1.0f) / (static_cast<float>(numberDash) * 2.0f)) * start_end);
			Vector2 new_end = step + start;
			glVertex2f(new_start.x, new_start.y);
			glVertex2f(new_end.x, new_end.y);
		}
	}
	else
	{
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);	
	}
	glEnd();

	glLineWidth(1);
	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]); 

}

void drawSquareCentered(Vector2 point, int w, int h, ColorStruct fill, ColorStruct stroke)
{
	std::vector<Vector2> points;
	int half_w = w / 2;
	int half_h = h / 2;
	points.push_back(Vector2(point.x - half_w, point.y - half_h));
	points.push_back(Vector2(point.x + half_w, point.y - half_h));
	points.push_back(Vector2(point.x + half_w, point.y + half_h));
	points.push_back(Vector2(point.x - half_w, point.y + half_h));

	drawPolygon(points, fill, stroke);
}

// Réfléchir comment utiliser le stroke et le fill proprement
void drawSquare(Vector2 point, int w, int h, ColorStruct fill, ColorStruct stroke)
{
	std::vector<Vector2> points;
	points.push_back(Vector2(point.x, point.y));
	points.push_back(Vector2(point.x + w, point.y));
	points.push_back(Vector2(point.x + w, point.y + h));
	points.push_back(Vector2(point.x, point.y + h));

	drawPolygon(points, fill, stroke);
}

void drawPolygon(std::vector<Vector2> points, ColorStruct fill, ColorStruct stroke)
{
    tools::unusedArg(stroke);

	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glColor4f(fill.r, fill.g, fill.b, fill.a);
	glBegin(GL_POLYGON);
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	
	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
}

void drawString(std::string label, Vector2 point, ColorStruct color)
{
	const char* msg = label.c_str();
	//int len = (int)strlen(msg);

	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glColor3f(color.r, color.g, color.b);
    glRasterPos2i(static_cast<GLint>(point.x), static_cast<GLint>(point.y));

	while (*msg != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *msg);
		++msg;
	}

	glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
}

void drawStringCentered(std::string label, Vector2 point, Vector2 rect, ColorStruct color, bool centeredOnX, bool centeredOnY)
{
	const unsigned char* msg = (unsigned char*)label.c_str();
	float fontx = point.x;
	float fonty = point.y;
	
	if (centeredOnX)
		fontx += (rect.x - glutBitmapLength(GLUT_BITMAP_HELVETICA_12, msg)) / 2.0f;
	if (centeredOnY)
		fonty += rect.y / 2.0f + glutBitmapHeight(GLUT_BITMAP_HELVETICA_12) / 4.0f;

	drawString(label, Vector2(fontx, fonty), color);
}

void drawCircle(Vector2 center, float radius, ColorStruct color, float step)
{
	std::vector<Vector2>points;

	for (float i = 0; i < 360; i += step)		// 360 degrés
	{
		float x = radius * cos(i / 180.0f * M_PI);
		float y = radius * sin(i / 180.0f * M_PI);
		points.push_back(Vector2(x, y) + center);
	}

	drawLines(points, color, 1, true);
}

int getXCoordInString(std::string label, Vector2 origin, int posChar)
{ 
	std::string subLabel = label.substr(0, posChar);

	return origin.x + glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (unsigned char*)subLabel.c_str());
}

int getSizeBetweenTwoPosInString(std::string label, int start, int end)
{
	if (end == -1)
		end = label.size() - 1;

	std::string subLabel = label.substr(start, (end - start));

	return glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (unsigned char*)subLabel.c_str());
}

int getPosInString(std::string label, int x_start, int x_current)
{
	uint cursor = -1;

	do
	{
		int size = getSizeBetweenTwoPosInString(label, 0, cursor + 1);
		int final_x = x_start + size;

		if (final_x > x_current)
			break;

		cursor++;

	} while (cursor != label.size());

	return cursor;
}
