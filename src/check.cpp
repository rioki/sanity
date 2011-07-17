// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#include "check.h"

#include <sstream>
#include "exceptions.h"

namespace sanity
{   
//------------------------------------------------------------------------------
    void do_assert(bool cond, const char* function, const char* str_cond)
    {
        if (! cond)
        {
           throw AssertFailed(function, str_cond); 
        }
    }
    
//------------------------------------------------------------------------------
    void do_require(bool cond, const char* function, const char* str_cond)
    {
        if (! cond)
        {
           throw RequireFailed(function, str_cond); 
        }
    }    
    
//------------------------------------------------------------------------------
    void do_ensure(bool cond, const char* function, const char* str_cond)
    {
        if (! cond)
        {
           throw EnsureFailed(function, str_cond); 
        }
    }
    
//------------------------------------------------------------------------------
    void do_fail(const char* function, const char* message)
    {
        throw Fail(function, message);
    }
    
//------------------------------------------------------------------------------
    void do_fail(const char* function, const std::string& message)
    {
        throw Fail(function, message);
    }

//------------------------------------------------------------------------------
    void do_check_argument(bool cond, const char* function, const char* str_cond)
    {
        if (! cond)
        {
           throw InvalidArgument(function, str_cond); 
        }
    }
}
