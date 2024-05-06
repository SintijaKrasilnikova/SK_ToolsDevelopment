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
    void SetMultipleSelected(bool areMultiSelected);
    void SetCamera(Camera* gameCamera) { camera = gameCamera; }

    void MoveSingle(InputCommands* Input);
    void MoveMultiple(InputCommands* Input);
    void AddToSelectedList(DisplayObject* disObj);

private:
    std::vector<DisplayObject> * displayList;
    std::vector<DisplayObject*>  selectedList;
    std::vector<int> selectedIDList;
    DisplayObject* selectedObject;
    Camera* camera;
    bool isObjectSelected = false;
    bool areMultipleSelected = false;
    int currentSelectedID = -1;
    float objectMoveSpeed;
    float objectRotSpeed;
    float objectScaleSpeed;


};

