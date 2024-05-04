#include "Camera.h"

#include <atltypes.h>

#include "InputCommands.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	//m_movespeed = 0.30;
	m_camRotRate = 3.0;
	m_camRotRateMouse = 7.f;
	m_movespeed = 0.30;
	m_movespeedUsual = 0.30;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_camMouseAngle.x = 0;
	m_camMouseAngle.y = 0;
	m_camMouseAngle.z = 0;

	canFocus = false;
	focusDistance = 5.f;
	inFocusTransition = false;
	
}

Camera::~Camera()
{

}

void Camera::Update(InputCommands* Input)
{
	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	if (Input->rotRight)
	{
		m_camPosition.y += m_movespeed;
	}
	if (Input->rotLeft)
	{
		m_camPosition.y -= m_movespeed;
	}

	if (Input->camFocusCalled == true && canFocus == true)
	{
		if (Input->rotRight)
		{
			m_camOrientation.y -= m_camRotRate;
		}
		if (Input->rotLeft)
		{
			m_camOrientation.y += m_camRotRate;
		}
	}


	if (Input->mouseRightPressed)
	{
		POINT p;
		if (GetCursorPos(&p))
		{
			m_mouseStartPos.x = p.x;
			m_mouseStartPos.y = p.y;

			Vector2 newCamLook = MouseRotate(m_mouseStartPos.x, m_mouseStartPos.y);

			m_camOrientation.y += newCamLook.y;
			m_camOrientation.z += newCamLook.x;
		}
	}


	//works kinda
	//x = rCos O Cos F
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.z) * 3.1415 / 180);
	//y = rsin F
	m_camLookDirection.y = sin((-m_camOrientation.z) * 3.1415 / 180);
	//z = rSin O Cos F
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.z) * 3.1415 / 180);

	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camRight.Cross(Vector3::UnitY, m_camUp);

	if (Input->camFocusCalled == false)
	{
		//process input and update 
		if (Input->forward)
		{
			m_camPosition += m_camLookDirection * m_movespeed;
		}
		if (Input->back)
		{
			m_camPosition -= m_camLookDirection * m_movespeed;
		}
		if (Input->right)
		{
			m_camPosition += m_camRight * m_movespeed;
		}
		if (Input->left)
		{
			m_camPosition -= m_camRight * m_movespeed;
		}
	}
	else
	{
		if (Input->forward)
		{
			focusDistance -= m_movespeed;
		}
		if (Input->back)
		{
			focusDistance += m_movespeed;
		}
	}
	

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	if (Input->camFocusCalled)
	{
		FocusOnObject();
	}

	if (Input->arcballMode == true)
	{
		ArcballCamera(Input);
	}

	//m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);
	//m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitZ, m_camForward);
	//apply camera vectors
	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

void Camera::SetWindowSize(float width, float height)
{
	windowWidth = width;
	windowHeight = height;
}

Vector2 Camera::MouseRotate(float m_x, float m_y)
{

	float deltax = m_x - (windowWidth / 2);
	float deltay = m_y - (windowHeight / 2);

	Vector2 new_rot;
	// Update the rotation.
	new_rot.y += deltax / m_camRotRateMouse;// m_speed * x;

	new_rot.x += deltay / m_camRotRateMouse;// m_speed * y;
	Vector2 cursor;
	cursor.x = windowWidth / 2;
	cursor.y = windowHeight / 2;
	//ClientToScreen(wnd, &cursor);
	SetCursorPos(cursor.x, cursor.y);

	return new_rot;
}

void Camera::ArcballCamera(InputCommands* Input)
{
	m_camLookAt = selectedObjectPosition;
	cameraDist = m_camLookDirection * focusDistance;

	////process input and update 
	//if (Input->forward)
	//{
	//	cameraDist -= m_camLookDirection * m_movespeed;
	//}
	//else if (Input->back)
	//{
	//	cameraDist += m_camLookDirection * m_movespeed;
	//}
	//else
	//{
	//	cameraDist = m_camLookDirection * focusDistance;
	//}

	m_camPosition = selectedObjectPosition - cameraDist;
	
}

void Camera::FocusOnObject()
{
	float focusTransitionSpeed = 3.f;
	//check if the last selected object has a valid ID
	if(canFocus == true)
	{
		inFocusTransition = true;


		m_camLookAt = selectedObjectPosition;
		DirectX::SimpleMath::Vector3 lookAtDifference = m_camLookDirection * focusDistance;
		DirectX::SimpleMath::Vector3 goalPosition = selectedObjectPosition - lookAtDifference;

		if (m_camPosition.x < goalPosition.x - focusTransitionSpeed - 0.1f)
		{
			m_camPosition.x += focusTransitionSpeed;
		}
		else if (m_camPosition.x > goalPosition.x + focusTransitionSpeed + 0.1f)
		{
			m_camPosition.x -=  focusTransitionSpeed;
		}
		else
		{
			m_camPosition.x = goalPosition.x;
		}

		if (m_camPosition.y < goalPosition.y - focusTransitionSpeed - 0.1f)
		{
			m_camPosition.y +=  focusTransitionSpeed;
		}
		else if (m_camPosition.y > goalPosition.y + focusTransitionSpeed + 0.1f)
		{
			m_camPosition.y -=  focusTransitionSpeed;
		}
		else
		{
			m_camPosition.y = goalPosition.y;
		}

		if (m_camPosition.z < goalPosition.z - focusTransitionSpeed - 0.1f)
		{
			m_camPosition.z += focusTransitionSpeed;
		}
		else if (m_camPosition.z > goalPosition.z + focusTransitionSpeed + 0.1f)
		{
			m_camPosition.z -= focusTransitionSpeed;
		}
		else
		{
			m_camPosition.z = goalPosition.z;
		}
		
	}
}


//Vector2 Camera::Turn(float d_x, float d_y)
//{
//	// Update the rotation.
//	rotation.y += (float)x / lookSpeed;// m_speed * x;
//
//	rotation.x += (float)y / lookSpeed;// m_speed * y;
//}


DirectX::SimpleMath::Matrix Camera::GetCameraView()
{
	return m_view;
}

DirectX::SimpleMath::Vector3 Camera::GetCameraPosition()
{
	return m_camPosition;
}

DirectX::SimpleMath::Vector3 Camera::GetCameraLookAt()
{
	return m_camLookAt;
}

DirectX::SimpleMath::Vector3 Camera::GetCameraRight()
{
	return m_camRight;
}

DirectX::SimpleMath::Vector3 Camera::GetCameraUp()
{
	return m_camUp;
}
