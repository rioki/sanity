// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include "sanity.h"

namespace sanity
{
    void write_crash_dump() noexcept;

    bool check_debugger() noexcept
    {
        #ifdef _WIN32
        return IsDebuggerPresent();
        #endif
        return false;
    }


    void debug_break()
    {
        #ifdef _WIN32
        DebugBreak();
        #endif
    }

    void fail(const std::string_view msg, const source_location location) noexcept
    {
        trace(msg, location);

        if (check_debugger())
        {
            debug_break();
        }

        write_crash_dump();

        std::terminate();
    }

    void check(bool condition, const std::string_view msg, const source_location location) noexcept
    {
        if (! condition)
        {
            fail(msg, location);
        }
    }
}
