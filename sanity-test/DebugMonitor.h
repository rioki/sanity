// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <mutex>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace test
{
    class DebugMonitor
    {
    public:
        DebugMonitor();
        ~DebugMonitor();

        [[nodiscard]] std::string get_output() const noexcept;

    private:
        mutable std::mutex mutex;
        std::stringstream  output;

        #ifdef _WIN32
        struct dbwin_buffer
        {
            DWORD dwProcessId;
            char  data[4096-sizeof(DWORD)];
        };

        HANDLE             buffer_ready_event;
        HANDLE             data_ready_event;
        HANDLE             mapped_file;
        dbwin_buffer*      buffer;
        std::jthread       thread;
        #endif

        DebugMonitor(const DebugMonitor&) = delete;
        DebugMonitor& operator = (const DebugMonitor&) = delete;
    };
}
