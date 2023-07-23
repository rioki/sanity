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

    void trace(const std::string_view message, const source_location location) noexcept
    {
        const auto line = std::format("{}({}): {}: {}\n", basename(location.file_name()), location.line(), location.function_name(), message);
        #ifdef _WIN32
        OutputDebugStringA(line.c_str());
        #else
        std::cerr << line;
        #endif
    }
}
