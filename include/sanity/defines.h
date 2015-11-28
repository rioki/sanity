// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#ifndef _SANITY_DEFINES_H_
#define _SANITY_DEFINES_H_

// TODO Add the other non standard function macros.
#if defined _MSC_VER
#define _SANITY_FUNCTION_ __FUNCTION__
#elif defined  __GNUC__
#define _SANITY_FUNCTION_ __PRETTY_FUNCTION__
#else
#define _SANITY_FUNCTION_ __func__
#endif

#ifdef ASSERT
#undef ASSERT
#endif



#endif
