#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;

	bool rotRight;
	bool rotLeft;

	bool mouseLeftPressed;
	bool mouseLeftReleased;

	bool mouseRightPressed;
	bool mouseRightReleased;

	int mouse_X;
	int mouse_Y;

	bool camFocusCalled;
};
