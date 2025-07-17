#ifndef MAIN_H
#define MAIN_H
const float dT = 1.0f; // krok czasowy
const int TPS = 60; // docelowa liczba ticków na sekundę
const float G = 30.0f; // stała grawitacyjna
// wciśnięcie klawiszy do sterowania kamerą
// 0 - góra, 1 - dół, 2 - prawo, 3 - lewo
inline bool keysDown[] = {false, false, false, false};

#endif
