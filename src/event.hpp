
#pragma	once
#include	"__common.hpp"
#include	<typeindex>
#include	<unordered_map>
#include	<list>

__begin_ns_td

class	event
{
public:
	event() = default;
	virtual ~event() = 0;
};

class	state_event : public event
{
public:
	enum state		state;
	class entity&	entity;
public:
	state_event(enum state state, class entity& entity) : state(state), entity(entity) {  }
	virtual ~state_event() = default;
};

__end_ns_td
