
#pragma	once
#include	"__common.hpp"
#include	"input_enum.hpp"

__begin_ns_td

KEY_ENUM();
MODIFIER_ENUM();
MOUSE_ENUM();

class	key
{
public:
	virtual ~key() = default;
};

class	single_key : public key
{
public:
	keycode	code;
public:
	single_key() = default;
	single_key(keycode code) : code(code) {  }
	virtual ~single_key() = default;
};

class	multi_key : public key
{
public:
	std::vector<keycode>	codes;
public:
	multi_key() = default;
	template	<typename ... types>
	multi_key(types&& ... args) : codes ({ std::forward<types>(args)... }) {  }
	virtual ~multi_key() = default;
};

__end_ns_td
