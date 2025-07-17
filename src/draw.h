#ifndef DRAW_H
#define DRAW_H
// pozycja kamery
inline float cam_x = 0;
inline float cam_y = 0;
// prędkość kamery
inline float cam_vx = 0;
inline float cam_vy = 0;
// domyślna wartość prędkości kamery (może być zmieniana)
inline float cam_v = 5.0f;

void draw(SDL_Renderer* renderer);
void updateCam();
#endif
