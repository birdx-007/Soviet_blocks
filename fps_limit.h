#pragma once
#include <windows.h>

struct fps_limit {

    int previous_time;
    int tpf_limit;
    int tpf;

    fps_limit(int fps = 60) : previous_time(GetTickCount64()), tpf(0) {
        limit_fps(fps);
    }
    void reset() {
        previous_time = GetTickCount64(),
            tpf = 0;
        tpf_limit = 60;
    }
    void limit_fps(int fps) {
        tpf_limit = (int)(1000.0f / (float)fps);
    }
    void delay() {
        tpf = GetTickCount64() - previous_time;

        if (tpf < tpf_limit)
            Sleep(tpf_limit - tpf - 1);

        previous_time = GetTickCount64();
    }
};