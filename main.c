#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800
#define TITLE         "Coordinate System"
#define SCALE         40.0f

float degrees_to_rad(float x)
{
    return x * (PI / 180.0f);
}

int main()
{
    printf("Hello, World\n");
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    SetTargetFPS(60);

    float amplitude = 1.0f;
    float frequency = 1.0f;
    float phase = 0.0f;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
         /* DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color); */
            DrawLine(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT, RED);
            DrawLine(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2, RED);

            int start_y = WINDOW_HEIGHT/2;
            for (int i = -10; i <= 10; i++) {
                int start_x = (WINDOW_WIDTH/2) + i * 40;
                char str[10];
                sprintf(str, "%d", i);
                /* DrawText(const char *text, int posX, int posY, int fontSize, Color color); */
                DrawText(str, start_x - 12, start_y + 10, 20, GREEN);
                /* DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color); */
                DrawLine(start_x, start_y + 5, start_x, start_y - 5, RED);

                if (i != 0) {
                    DrawText(str, (WINDOW_WIDTH/2) - 30, ((start_y + 10) + i * (-1) * 40), 20, GREEN);
                    DrawLine(WINDOW_WIDTH/2 - 5, 
                            ((start_y + 10) + i * (-1) * 40), 
                            (WINDOW_WIDTH/2 + 5), 
                            ((start_y + 10) + i * (-1) * 40), RED);
                }

            }

            if (IsKeyDown(KEY_A)) amplitude += 0.1f;
            if (IsKeyDown(KEY_Z)) amplitude -= 0.1f;
            amplitude = fmaxf(0.1f, amplitude);

            if (IsKeyDown(KEY_F)) frequency += 0.1f;
            if (IsKeyDown(KEY_C)) frequency -= 0.1f;
            frequency = fmaxf(0.1f, frequency);

            if (IsKeyDown(KEY_P)) phase += 0.1f;
            if (IsKeyDown(KEY_Q)) phase -= 0.1f;

            for (float x = -10.0f; x <= 10.0f; x += 0.1f) {
                /* float y = sinf(x); */
                float y = amplitude * sinf(frequency * degrees_to_rad(x) + phase);
                int screen_x = WINDOW_WIDTH/2.0f + x * SCALE;
                int screen_y = WINDOW_HEIGHT/2.0f - y * SCALE;
                DrawPixel(screen_x, screen_y, BLUE);
            }
            char infor[200];
            sprintf(infor, 
                    "amplitude (A(up)/Z(down)): %.2f\n" 
                    "frequency (F(up)/C(down)): %.2f\n" 
                    "phase (P(up)/Q(down)): %.2f\n",
                    amplitude, frequency, phase);
            DrawText(infor, 10, 10, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
