#ifndef DRAW_H
#define DRAW_H
// the camera's position
inline float cam_x = 0;
inline float cam_y = 0;
// the camera's velocity
inline float cam_vx = 0;
inline float cam_vy = 0;
// default value for the camera's velocity, it can be changed later by the user
inline float cam_v = 0.2f;

void draw(SDL_Renderer* renderer);
void updateCam();
#endif
