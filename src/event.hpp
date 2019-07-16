
#pragma	once
#include	"__common.hpp"
#include	<list>

__begin_ns_td

class	event_manager
{
public:
	std::list<std::unique_ptr<event>>	events;
public:
	event_manager() = default;
	~event_manager() = default;
};

class	event
{
public:
	event() = default;
	virtual ~event() = 0;
};

__end_ns_td
