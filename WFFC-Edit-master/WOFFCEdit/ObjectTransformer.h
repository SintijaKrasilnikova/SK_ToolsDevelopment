#pragma once
#include "Camera.h"
#include "DisplayObject.h"

class InputCommands;


class ObjectTransformer
{

public:
    ObjectTransformer();
    ~ObjectTransformer();

    void Update(InputCommands* Input);
    //void SetDisplayList(std::vector<DisplayObject>* passedList) { displayList = passedList; }
    void SetSelectedObject(DisplayObject* newObject) { selectedObject = newObject; }
    void SetIsObjectSelected(bool isSelected, int objectID) { isObjectSelected = isSelected; currentSelectedID = objectID; }
    void SetCamera(Camera* gameCamera) { camera = gameCamera; }

private:
    //std::vector<DisplayObject> * displayList;
    DisplayObject* selectedObject;
    Camera* camera;
    bool isObjectSelected = false;
    int currentSelectedID = -1;
    float objectMoveSpeed;


};

