
#pragma	once
#include	"__common.hpp"

__begin_ns_td

class	event_handler
{
public:
	event_handler() = default;
	~event_handler() = default;
};

class	event
{
public:
	event() = default;
	virtual ~event() = 0;
};

class	input_event : public event
{
protected:
	action	__action;
public:
	input_event(action action) : __action(action) {  }
	virtual ~input_event() = default;
	inline __attribute__((always_inline))
	const action&	action() const
	{
		return __action;
	}
};

__end_ns_td
