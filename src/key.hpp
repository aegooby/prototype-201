
#pragma	once
#include	"__common.hpp"
#include	"input_enum.hpp"

__begin_ns_td

KEY_ENUM();
MODIFIER_ENUM();
MOUSE_ENUM();

enum	keystate
{
	up,
	down,
	scan,
	size,
};

class	key_base
{
public:
	key_base() = default;
	virtual ~key_base() = default;
};

class	key : public key_base
{
protected:
	const keycode	__code;
	keystate		__state;
public:
	key(keycode code) : __code(code) {  }
	virtual ~key() = default;
	inline __attribute__((always_inline))
	void	state(const keystate& state)
	{
		__state = state;
	}
	inline __attribute__((always_inline))
	const keystate&	state() const
	{
		return __state;
	}
	inline __attribute__((always_inline))
	const keycode&	code() const
	{
		return __code;
	}
};

class	key_chord : public key_base
{
public:
	std::vector<key>	keys;
public:
	template	<typename ... types>
	key_chord(types ... keys) : keys({ keys ... }) {  }
	virtual ~key_chord() = default;
	inline __attribute__((always_inline))
	size_t	count() const
	{
		return keys.size();
	}
};

__end_ns_td
