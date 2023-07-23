// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <version>
#include <exception>
#include <string_view>
#ifdef __cpp_lib_source_location
#include <source_location>
#endif
#include <array>
#include <format>
#include <filesystem>

#if _WIN32
#include <Windows.h>
#include <dbghelp.h>
#endif
