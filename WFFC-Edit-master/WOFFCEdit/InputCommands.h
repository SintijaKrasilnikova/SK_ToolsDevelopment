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
	bool arcballMode;

	bool moveObjectRight;
	bool moveObjectLeft;

	bool moveObjectForward;
	bool moveObjectBack;

	bool rotateObjectYawRight;
	bool rotateObjectYawLeft;

	bool rotateObjectPitchRight;
	bool rotateObjectPitchLeft;

	bool rotateObjectRollRight;
	bool rotateObjectRollLeft;

	bool scaleUp;
	bool scaleDown;

	bool copyCalled;
	bool pasteCalled;

	bool multipleSelection;
};
