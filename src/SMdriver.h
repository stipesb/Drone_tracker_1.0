#ifndef SMdriver_h
#define SMdriver_h

#include <Arduino.h>
class vector_control {
public:
vector_control();
~vector_control();
void SetupZaBrojac();
void klik();
void tick(int x, int y);
void test();
};
#endif

