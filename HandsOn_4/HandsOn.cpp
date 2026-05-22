#include "raylib.h"
#include <cmath>
#include "rlgl.h"

int main()
{
    InitWindow(1400, 850, "Transformaciones Matematicas 2D y 3D - Raylib");

    Camera3D camera = { 0 };
    camera.position = { 0.0f, 20.0f, 22.0f };
    camera.target = { 0.0f, 3.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    float reboteY = 1.0f;
    float velocidadY = 0.10f;

    float traslacionX = -2.0f;
    float velocidadX = 0.05f;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        float t = (float)GetTime();

        // -----------------------------
        // MOVIMIENTO SENOIDAL
        // -----------------------------
        float senoY = 2.0f + sinf(t * 2.0f) * 1.5f;

        // -----------------------------
        // REBOTE
        // -----------------------------
        reboteY += velocidadY;

        if (reboteY > 4.0f || reboteY < 1.0f)
        {
            velocidadY *= -1.0f;
        }

        // -----------------------------
        // ORBITA
        // -----------------------------
        float radioOrbita = 2.2f;

        float orbitaX = cosf(t) * radioOrbita;
        float orbitaZ = sinf(t) * radioOrbita;

        // -----------------------------
        // TRAYECTORIA
        // -----------------------------
        float trayectoriaX = -2.5f + fmodf(t * 1.5f, 5.0f);
        float trayectoriaZ = sinf(t * 3.0f) * 1.3f;

        // -----------------------------
        // TRASLACION
        // -----------------------------
        traslacionX += velocidadX;

        if (traslacionX > 2.0f)
        {
            traslacionX = -2.0f;
        }

        // -----------------------------
        // ROTACION
        // -----------------------------
        float anguloRotacion = t * 90.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(40, 1.0f);

        // ======================================================
        // ZONAS
        // ======================================================

        DrawCube({ -12.0f, 0.05f, 6.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);
        DrawCube({ -4.0f, 0.05f, 6.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);
        DrawCube({  4.0f, 0.05f, 6.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);
        DrawCube({ 12.0f, 0.05f, 6.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        DrawCube({ -12.0f, 0.05f, -4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);
        DrawCube({ -4.0f, 0.05f, -4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        // ======================================================
        // 1. MOVIMIENTO SENOIDAL
        // ======================================================

        DrawLine3D(
            { -12.0f, 1.0f, 6.0f },
            { -12.0f, 4.0f, 6.0f },
            BLUE
        );

        DrawSphere({ -12.0f, senoY, 6.0f }, 0.5f, BLUE);

        // ======================================================
        // 2. REBOTE
        // ======================================================

        DrawCube(
            { -4.0f, reboteY, 6.0f },
            1.0f,
            1.0f,
            1.0f,
            RED
        );

        DrawLine3D(
            { -4.0f, 1.0f, 6.0f },
            { -4.0f, 4.0f, 6.0f },
            RED
        );

        // ======================================================
        // 3. ORBITA
        // ======================================================

        DrawSphere({ 4.0f, 1.0f, 6.0f }, 0.25f, DARKGREEN);

        DrawSphere(
            { 4.0f + orbitaX, 1.0f, 6.0f + orbitaZ },
            0.45f,
            GREEN
        );

        DrawSphereWires(
            { 4.0f, 1.0f, 6.0f },
            radioOrbita,
            24,
            24,
            DARKGREEN
        );

        // ======================================================
        // 4. TRAYECTORIA
        // ======================================================

        for (int i = 0; i < 80; i++)
        {
            float x1 = -2.5f + i * (5.0f / 80.0f);
            float x2 = -2.5f + (i + 1) * (5.0f / 80.0f);

            float z1 = sinf(x1 * 3.0f) * 1.3f;
            float z2 = sinf(x2 * 3.0f) * 1.3f;

            DrawLine3D(
                { 12.0f + x1, 1.0f, 6.0f + z1 },
                { 12.0f + x2, 1.0f, 6.0f + z2 },
                ORANGE
            );
        }

        DrawSphere(
            { 12.0f + trayectoriaX, 1.0f, 6.0f + trayectoriaZ },
            0.45f,
            ORANGE
        );

        // ======================================================
        // 5. TRASLACION
        // ======================================================

        DrawCube(
            { -12.0f + traslacionX, 1.0f, -4.0f },
            1.5f,
            1.5f,
            1.5f,
            PURPLE
        );

        DrawLine3D(
            { -14.0f, 1.0f, -4.0f },
            { -10.0f, 1.0f, -4.0f },
            DARKPURPLE
        );

        // ======================================================
        // 6. ROTACION
        // ======================================================

        DrawCylinderEx(
            { -4.0f, 0.2f, -4.0f },
            { -4.0f, 3.0f, -4.0f },
            0.15f,
            0.15f,
            20,
            DARKGRAY
        );

        rlPushMatrix();

        rlTranslatef(-4.0f, 3.0f, -4.0f);
        rlRotatef(anguloRotacion, 0.0f, 1.0f, 0.0f);

        DrawCube(
            { 0.0f, 0.0f, 0.0f },
            2.5f,
            0.3f,
            0.8f,
            MAROON
        );

        rlPopMatrix();

        EndMode3D();

        // ======================================================
        // TEXTOS
        // ======================================================

        DrawText(
            "HandsOn 4 - Transformaciones Matematicas 2D y 3D - Raylib",
            20,
            20,
            32,
            DARKGRAY
        );

        DrawText("1. Movimiento senoidal", 70, 90, 22, BLUE);
        DrawText("Oscilacion usando funcion seno", 70, 120, 18, GRAY);

        DrawText("2. Rebote", 360, 90, 22, RED);
        DrawText("Cambio de direccion por colision", 360, 120, 18, GRAY);

        DrawText("3. Orbita", 640, 90, 22, GREEN);
        DrawText("Movimiento circular alrededor de un punto", 640, 120, 18, GRAY);

        DrawText("4. Trayectoria", 1020, 90, 22, ORANGE);
        DrawText("Recorrido sobre una curva", 1020, 120, 18, GRAY);

        DrawText("5. Traslacion", 110, 520, 22, PURPLE);
        DrawText("Desplazamiento lineal en el espacio", 110, 550, 18, GRAY);

        DrawText("6. Rotacion", 430, 520, 22, MAROON);
        DrawText("Giro alrededor de un eje", 430, 550, 18, GRAY);

        DrawText(
            "La escena divide cada transformacion para facilitar su analisis visual.",
            20,
            760,
            20,
            DARKGRAY
        );
        DrawText("ESC para salir", 20, 790, 20, DARKGRAY);
        EndDrawing();
    }

        

    CloseWindow();
    return 0;
}