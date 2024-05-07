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
	MoveSingle(Input);
	MoveMultiple(Input);
}

void ObjectTransformer::SetMultipleSelected(bool areMultiSelected)
{
	areMultipleSelected = areMultiSelected;

	//if multi selection was ended, clear the list
	if(areMultiSelected == false)
	{
		for (unsigned int i = 0; i < selectedList.size(); i++)
		{
			selectedList[i]->m_wireframe = false;
		}
		selectedList.clear();
	}
}

void ObjectTransformer::MoveSingle(InputCommands* Input)
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

		if (Input->rotateObjectYawLeft)
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
		//scale gets bigger/smaller in all directions
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

void ObjectTransformer::MoveMultiple(InputCommands* Input)
{
	if(areMultipleSelected && selectedList.empty() != true )
	{
		for (unsigned int i = 0; i < selectedList.size(); i++)
		{
			
			if (Input->moveObjectRight)
			{
				selectedList[i]->m_position += objectMoveSpeed * camera->GetCameraRight();
			}
			if (Input->moveObjectLeft)
			{
				selectedList[i]->m_position -= objectMoveSpeed * camera->GetCameraRight();
			}

			if (Input->moveObjectForward)
			{
				selectedList[i]->m_position -= objectMoveSpeed * camera->GetCameraUp();
			}

			if (Input->moveObjectBack)
			{
				selectedList[i]->m_position += objectMoveSpeed * camera->GetCameraUp();
			}

			if (Input->rotateObjectYawLeft)
			{
				selectedList[i]->m_orientation.x -= objectRotSpeed;
			}
			if (Input->rotateObjectYawRight)
			{
				selectedList[i]->m_orientation.x += objectRotSpeed;
			}

			if (Input->rotateObjectPitchLeft)
			{
				selectedList[i]->m_orientation.y -= objectRotSpeed;
			}
			if (Input->rotateObjectPitchRight)
			{
				selectedList[i]->m_orientation.y += objectRotSpeed;
			}

			if (Input->rotateObjectRollLeft)
			{
				selectedList[i]->m_orientation.z -= objectRotSpeed;
			}
			if (Input->rotateObjectRollRight)
			{
				selectedList[i]->m_orientation.z += objectRotSpeed;
			}

			//scale gets bigger/smaller in all directions
			if (Input->scaleUp)
			{
				selectedList[i]->m_scale += DirectX::SimpleMath::Vector3(objectScaleSpeed, objectScaleSpeed, objectScaleSpeed);
			}
			if (Input->scaleDown)
			{
				selectedList[i]->m_scale -= DirectX::SimpleMath::Vector3(objectScaleSpeed, objectScaleSpeed, objectScaleSpeed);
			}
		}
	}
}

void ObjectTransformer::AddToSelectedList(DisplayObject* disObj)
{
	//check if the object is already in the list
	//un-pick if it is
	for (unsigned int i = 0; i < selectedList.size(); i++)
	{
		if(selectedList[i] == disObj)
		{
			//https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/

			auto it = std::find(selectedList.begin(), selectedList.end(), selectedList[i]);
			if (it != selectedList.end()) {
				disObj->m_wireframe = false;
				selectedList.erase(it);
				objRemoved = true;
			}
		}
	}
	if (objRemoved == false)
	{
		disObj->m_wireframe = true;
		selectedList.push_back(disObj);
	}
	objRemoved = false;
}
