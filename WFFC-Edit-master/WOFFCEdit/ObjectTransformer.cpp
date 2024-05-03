#include "ObjectTransformer.h"

#include "InputCommands.h"

ObjectTransformer::ObjectTransformer()
{
	objectMoveSpeed = 0.15f;
}

ObjectTransformer::~ObjectTransformer()
{
}

void ObjectTransformer::Update(InputCommands* Input)
{
	if (isObjectSelected == true)
	{
		if (Input->moveObjectRight)
		{
			selectedObject->m_position += objectMoveSpeed * camera->GetCameraRight();
		}

		if (Input->moveObjectLeft)
		{
			selectedObject->m_position -= objectMoveSpeed * camera->GetCameraRight();
		}

		if (Input->moveObjectForward)
		{
			selectedObject->m_position -= objectMoveSpeed * camera->GetCameraUp();
		}

		if (Input->moveObjectBack)
		{
			selectedObject->m_position += objectMoveSpeed * camera->GetCameraUp();
		}
	}
}
