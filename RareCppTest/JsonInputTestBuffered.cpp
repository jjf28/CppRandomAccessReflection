#define USE_BUFFERED_STREAMS

#define GET_RUNJSONINPUTTESTSRC_INCLUDES
#include "JsonInputTest.cpp"
#undef GET_RUNJSONINPUTTESTSRC_INCLUDES

namespace Buffered
{
#define GET_RUNJSONINPUTTESTSRC_CPP
#include "JsonInputTest.cpp"
#undef GET_RUNJSONINPUTTESTSRC_CPP
}

#undef USE_BUFFERED_STREAMS
