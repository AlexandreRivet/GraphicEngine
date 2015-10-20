#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct s_mouse
{
	int x;
	int y;
	bool left_button_pressed;
	bool middle_button_pressed;
	bool right_button_pressed;
} Mouse;

typedef struct s_color
{
	float r;
	float g;
	float b;
	float a;
} Color;

#endif