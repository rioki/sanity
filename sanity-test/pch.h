// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <gtest/gtest.h>

#include <mutex>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#include <tlhelp32.h>
#else
#include <unistd.h>
#endif

template <typename T>
void sleep_for(const T duration)
{
    #ifdef _WIN32
    std::this_thread::sleep_for(duration);
    #else
    usleep(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
    #endif
}
