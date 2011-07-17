// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#include "exceptions.h"

#include <sstream>

namespace sanity
{
//------------------------------------------------------------------------------
    CheckFailed::CheckFailed(const std::string& t, const std::string& f, const std::string& m)
    : std::logic_error(std::string()), type(t), function(f), message(m) {}
        
//------------------------------------------------------------------------------
    const std::string& CheckFailed::get_type() const
    {
        return type;
    }
    
//------------------------------------------------------------------------------
    const std::string& CheckFailed::get_function() const
    {
        return function;
    }
    
//------------------------------------------------------------------------------
    const std::string& CheckFailed::get_message() const
    {
        return message;
    }
    
//------------------------------------------------------------------------------
    const char* CheckFailed::what() const throw()
    {
        if (full_message.empty())
        {
            std::stringstream buff;
            buff << type << ": " << function << ": " << message;
            full_message = buff.str();
        }
        return full_message.c_str();
    }    
    
//------------------------------------------------------------------------------
    AssertFailed::AssertFailed(const std::string& f, const std::string& m)
    : CheckFailed("ASSERT", f, m) {}

//------------------------------------------------------------------------------
    Fail::Fail(const std::string& f, const std::string& m)
    : CheckFailed("FAIL", f, m) {}
    
//------------------------------------------------------------------------------
    RequireFailed::RequireFailed(const std::string& f, const std::string& m)
    : CheckFailed("REQUIRE", f, m) {}
    
//------------------------------------------------------------------------------
    EnsureFailed::EnsureFailed(const std::string& f, const std::string& m)
    : CheckFailed("ENSURE", f, m) {}
    
//------------------------------------------------------------------------------
    InvalidArgument::InvalidArgument(const std::string& f, const std::string& m)
    : std::invalid_argument(std::string()), function(f), message(m) {}
    
//------------------------------------------------------------------------------
    const std::string& InvalidArgument::get_function() const
    {
        return function;
    }
    
//------------------------------------------------------------------------------
    const std::string& InvalidArgument::get_message() const
    {
        return message;
    }
    
//------------------------------------------------------------------------------
    const char* InvalidArgument::what() const throw()
    {
        if (full_message.empty())
        {
            std::stringstream buff;
            buff << "INVALID ARGUMENT: " << function << ": " << message;
            full_message = buff.str();
        }
        return full_message.c_str();
    }
}
