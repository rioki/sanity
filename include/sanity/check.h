// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#ifndef _SANITY_CHECK_H_
#define _SANITY_CHECK_H_

#include <string>

#include "defines.h"

namespace sanity
{  
    /**
     * Implementation for the ASSERT macro.
     **/
    _SANITY_EXPORT
    void do_assert(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the REQUIRE macro.
     **/
    _SANITY_EXPORT
    void do_require(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the ENSURE macro.
     **/
    _SANITY_EXPORT
    void do_ensure(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the FAIL macro.
     *
     * @{
     **/
    _SANITY_EXPORT
    void do_fail(const char* function, const char* message);
    _SANITY_EXPORT
    void do_fail(const char* function, const std::string& message);
    /** @} **/

    /**
     * Implementation for the CHECK_ARGUMENT macro.
     **/
    _SANITY_EXPORT
    void do_check_argument(bool cond, const char* function, const char* str_cond);
}

#define ASSERT(COND) ::sanity::do_assert(COND, _SANITY_FUNCTION_, #COND)
#define REQUIRE(COND) ::sanity::do_require(COND, _SANITY_FUNCTION_, #COND)
#define ENSURE(COND) ::sanity::do_ensure(COND, _SANITY_FUNCTION_, #COND)
#define FAIL(MSG) ::sanity::do_fail(_SANITY_FUNCTION_, MSG)

#define CHECK_ARGUMENT(COND) ::sanity::do_check_argument(COND, _SANITY_FUNCTION_, #COND)

#endif
