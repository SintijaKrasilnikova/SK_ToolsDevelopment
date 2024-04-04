#pragma once

#include "DisplayChunk.h"


class InputCommands;


class Camera
{

public:
    Camera();
    ~Camera();

    DirectX::SimpleMath::Matrix GetCameraView();
    DirectX::SimpleMath::Vector3 GetCameraPosition();
    DirectX::SimpleMath::Vector3 GetCameraLookAt();
    void Update(InputCommands* Input);
    void SetWindowSize(float width, float height);

    void setFocusObjectsPos(DirectX::SimpleMath::Vector3 position) { selectedObjectPosition = position; }
    void setCanFocus(bool canCameraFocus) { canFocus = canCameraFocus; }
  

private:
    DirectX::SimpleMath::Vector2 MouseRotate(float m_x, float m_y);
    void FocusOnObject();
    

    //int m_selectedObjectID = -1;
    DirectX::SimpleMath::Vector3 selectedObjectPosition;
    bool canFocus;
    float focusDistance;

    bool inFocusTransition;

    //DirectX::SimpleMath::Vector2 Turn(float d_x, float d_y);

    //void Update(DX::StepTimer const& timer);
    
    //void CameraFunctionality();
    

    //InputCommands						m_InputCommands;

    //functionality
    float								m_movespeed;


    //// Input devices.
    //std::unique_ptr<DirectX::GamePad>       m_gamePad;
    //std::unique_ptr<DirectX::Keyboard>      m_keyboard;
    //std::unique_ptr<DirectX::Mouse>         m_mouse;


    //camera variables for world space
    DirectX::SimpleMath::Matrix                 m_world;
    DirectX::SimpleMath::Matrix                 m_view;
    DirectX::SimpleMath::Matrix                 m_projection;

    //camera
    DirectX::SimpleMath::Vector3		m_camPosition;
    DirectX::SimpleMath::Vector3		m_camOrientation;
    DirectX::SimpleMath::Vector3		m_camLookAt;
    DirectX::SimpleMath::Vector3		m_camLookDirection;
    DirectX::SimpleMath::Vector3		m_camRight;
    DirectX::SimpleMath::Vector3		m_camMouseAngle;
    float m_camRotRate;
    float m_camRotRateMouse;

    DirectX::SimpleMath::Vector2 m_mouseStartPos;
    DirectX::SimpleMath::Vector2 m_mouseEndPos;

    float m_pitch;
    float m_yaw;

    float windowWidth;
    float windowHeight;

};

