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
    std::string basename(const std::string& file) noexcept
    {
        auto i = file.find_last_of("\\/");
        if (i == std::string::npos)
        {
            return file;
        }
        else
        {
            return file.substr(i + 1);
        }
    }

    std::string funcname(const std::string& func) noexcept
    {
        auto i = func.find_last_of(":");
        auto j = func.find_first_of("(");
        if (i == std::string::npos)
        {
            return func;
        }
        else
        {
            auto d = j - i - 2;         // j is allowed to be npos
            if (d > (func.length() - i + 1))  // handle j == npos
            {
                d = (func.length() - i + 1);
            }
            return func.substr(i + 1, d);
        }
    }

    void trace(const std::string_view message, const source_location location) noexcept
    {
        #ifdef _WIN32
        const auto line = std::format("{}({}): {}: {}\n", basename(location.file_name()), location.line(), funcname(location.function_name()), message);
        OutputDebugStringA(line.c_str());
        #else
        std::cerr << basename(location.file_name()) << "(" << location.line() << "): " << funcname(location.function_name()) << ": " << message << std::endl;
        #endif
    }
}
