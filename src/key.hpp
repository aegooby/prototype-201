
#pragma once
#include "__common.hpp"
#include "input_enum.hpp"

#include <vector>

namespace p201
{

/**
 * @brief These macros were defined in another file for the sake of conserving
 *        space in this file since they are very long.
 * @see input_enum.hpp
 */
KEY_ENUM();
MODIFIER_ENUM();
MOUSE_ENUM();

class key
{
public:
    virtual ~key() = default;
};

class single_key : public key
{
public:
    keycode code;

public:
    single_key() = default;
    single_key(keycode code) : code(code) { }
    virtual ~single_key() = default;
};

class multi_key : public key
{
public:
    std::vector<keycode> codes;

public:
    multi_key() = default;
    template<typename... types>
    multi_key(types&&... args) : codes({ std::forward<types>(args)... })
    {
    }
    virtual ~multi_key() = default;
};

} // namespace p201
