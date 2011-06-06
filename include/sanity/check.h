// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#ifndef _SANITY_CHECK_H_
#define _SANITY_CHECK_H_

#include <stdexcept>
#include <string>

#include "defines.h"

namespace sanity
{
    /**
     * Exception that is raised of a check fails. 
     **/
    class CheckFailed : public std::logic_error
    {
    public:
        
        CheckFailed(const std::string& type, const std::string& function, const std::string& message);
        
        ~CheckFailed() throw () {}
        
        const std::string& get_type() const;
        
        const std::string& get_function() const;
        
        const std::string& get_message() const;
        
        virtual const char* what() const throw();
        
    private:
        std::string type;
        std::string function;
        std::string message;
        mutable std::string full_message;
    };
    
    class AssertFailed : public CheckFailed
    {
    public:
        
        AssertFailed(const std::string& function, const std::string& message);
    };
    
    class Fail : public CheckFailed
    {
    public:
        
        Fail(const std::string& function, const std::string& message);
    };
    
    class RequireFailed : public CheckFailed
    {
    public:
        
        RequireFailed(const std::string& function, const std::string& message);
    };
    
    class EnsureFailed : public CheckFailed
    {
    public:
        
        EnsureFailed(const std::string& function, const std::string& message);
    };
    
    class InvalidArgument : public std::invalid_argument
    {
    public:
        
        InvalidArgument(const std::string& function, const std::string& message);
        
        ~InvalidArgument() throw() {}
        
        const std::string& get_function() const;
        
        const std::string& get_message() const;
        
        virtual const char* what() const throw();
        
    private:
        std::string function;
        std::string message;
        mutable std::string full_message;
    };
    
    /**
     * Implementation for the ASSERT macro.
     **/
    void do_assert(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the REQUIRE macro.
     **/
    void do_require(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the ENSURE macro.
     **/
    void do_ensure(bool cond, const char* function, const char* str_cond);
    
    /**
     * Implementation for the FAIL macro.
     *
     * @{
     **/
    void do_fail(const char* function, const char* message);
    void do_fail(const char* function, const std::string& message);
    /** @} **/

    /**
     * Implementation for the CHECK_ARGUMENT macro.
     **/
    void do_check_argument(bool cond, const char* function, const char* str_cond);
}

#define ASSERT(COND) ::sanity::do_assert(COND, _SANITY_FUNCTION_, #COND)
#define REQUIRE(COND) ::sanity::do_require(COND, _SANITY_FUNCTION_, #COND)
#define ENSURE(COND) ::sanity::do_ensure(COND, _SANITY_FUNCTION_, #COND)
#define FAIL(MSG) ::sanity::do_fail(_SANITY_FUNCTION_, MSG)

#define CHECK_ARGUMENT(COND) ::sanity::do_check_argument(COND, _SANITY_FUNCTION_, #COND)

#endif
