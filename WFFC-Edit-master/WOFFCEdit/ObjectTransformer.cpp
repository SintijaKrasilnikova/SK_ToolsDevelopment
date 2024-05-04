#include "ObjectTransformer.h"

#include "InputCommands.h"

ObjectTransformer::ObjectTransformer()
{
	objectMoveSpeed = 0.15f;
	objectRotSpeed = 1.5f;
	objectScaleSpeed = 0.05f;
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

		if(Input->rotateObjectYawLeft)
		{
			selectedObject->m_orientation.x -= objectRotSpeed;
		}
		if (Input->rotateObjectYawRight)
		{
			selectedObject->m_orientation.x += objectRotSpeed;
		}

		if (Input->rotateObjectPitchLeft)
		{
			selectedObject->m_orientation.y -= objectRotSpeed;
		}
		if (Input->rotateObjectPitchRight)
		{
			selectedObject->m_orientation.y += objectRotSpeed;
		}

		if (Input->rotateObjectRollLeft)
		{
			selectedObject->m_orientation.z -= objectRotSpeed;
		}
		if (Input->rotateObjectRollRight)
		{
			selectedObject->m_orientation.z += objectRotSpeed;
		}

		if (Input->scaleUp)
		{
			selectedObject->m_scale += DirectX::SimpleMath::Vector3(objectScaleSpeed, objectScaleSpeed, objectScaleSpeed);
		}
		if (Input->scaleDown)
		{
			selectedObject->m_scale -= DirectX::SimpleMath::Vector3(objectScaleSpeed, objectScaleSpeed, objectScaleSpeed);
		}
	}
}
