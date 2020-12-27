
#pragma once
#include "__common.hpp"

namespace p201
{
/** @brief Macro to only run a statement in debug mode. */
#if defined(P201_DEBUG)
#    define debug(statement) statement
#else
#    define debug(statement)
#endif
} // namespace p201
