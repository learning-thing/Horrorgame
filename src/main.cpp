#include <iostream>
#include <raylib.h>
#include "movement.hpp"

int main() {
    std::cout << "hello world\n";
    float iTime = 0;
    int screenWidth = 1920;
    int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Hello World");
    ToggleBorderlessWindowed();
    SetTargetFPS(100);
    DisableCursor();
    InitAudioDevice();      // Initialize audio device


    Shader BasicLighting = LoadShader("res/shaders/baselight.vs", "res/shaders/baselight.fs");
    Shader PostFX = LoadShader(0, "res/shaders/post_processing.fs");
    Vector3 LightPos = (Vector3){0, 10, 0};

    int MatModelLoc = GetShaderLocation(BasicLighting, "matModel");
    int camPosLoc = GetShaderLocation(BasicLighting, "viewPos");
    int iTimeLoc = GetShaderLocation(BasicLighting, "iTime");
    int lightposLoc = GetShaderLocation(BasicLighting, "LightPos");
    int ambientLoc = GetShaderLocation(BasicLighting, "ambientColor");

    SetShaderValue(BasicLighting, lightposLoc, &LightPos, SHADER_UNIFORM_VEC3);

    Vector3 ambientColor = (Vector3){1, 1, 1};

    AOTMovement movement;
    Camera3D camera;
    camera.position = (Vector3){ 0.0f, 3.0f, -3.0f };
    camera.target = (Vector3){ 0.0f, 3.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy= 60.0f;
    camera.projection = CAMERA_PERSPECTIVE; 

    SetShaderValue(BasicLighting, camPosLoc, &camera.position.x, SHADER_UNIFORM_VEC3);
    SetShaderValue(BasicLighting, ShaderLocationIndex(BasicLighting.locs[SHADER_LOC_MATRIX_MODEL]), &ambientColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(BasicLighting, iTimeLoc, &iTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(BasicLighting, ambientLoc, &ambientColor, SHADER_UNIFORM_VEC3);
    //Generate list of trees

    // Create a RenderTexture2D to be used for render to texture
    RenderTexture2D PostProcessingLayer = LoadRenderTexture(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        //Update Stuff
        iTime+=GetFrameTime();
        camera.target = movement.CamTargPos().toRayVec();
        movement.rotation = -(float)GetMouseX()/1000;
        movement.upAngle = (float)GetMouseY()/1000;
        LightPos = camera.position;
        SetShaderValue(BasicLighting, camPosLoc, &camera.position, SHADER_UNIFORM_VEC3);
        SetShaderValue(BasicLighting, iTimeLoc, &iTime, SHADER_UNIFORM_FLOAT);
        camera.position = movement.update(GetFrameTime());

        camera.fovy+=(movement.fov-camera.fovy)*.5;
        BeginTextureMode(PostProcessingLayer);
            //Draw Stuff
            ClearBackground((Color){10, 10, 18});

            BeginMode3D(camera);
                BeginShaderMode(BasicLighting);
                    DrawPlane((Vector3){0, 0, 0}, (Vector2){10, 10}, WHITE);
                EndShaderMode();
            EndMode3D();
        EndTextureMode();
        
        BeginDrawing();
            ClearBackground((Color){10, 10, 18});
            BeginShaderMode(PostFX);
                DrawTextureRec(PostProcessingLayer.texture, (Rectangle){ 0, 0, (float)PostProcessingLayer.texture.width, (float)-PostProcessingLayer.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            
            //Without postFX
            BeginMode3D(camera);
                DrawGrid(10, 10);
            EndMode3D();

            //CrossHair point
            DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 2, WHITE);
            DrawFPS(10, 10);
        
        EndDrawing();
    }
    
    UnloadShader(BasicLighting);
    CloseWindow();
    return 0;
}
