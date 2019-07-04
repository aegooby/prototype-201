
#pragma	once
#include	"__common.hpp"
#include	<list>

__begin_ns_td

class	event_handler
{
public:
	std::list<std::unique_ptr<event>>	events;
public:
	event_handler() = default;
	~event_handler() = default;
	void	add_event(std::unique_ptr<td::event>&& event)
	{
		events.emplace_back(std::forward<std::unique_ptr<td::event>>(event));
	}
	void	remove_event(const std::unique_ptr<td::event>& event)
	{
		events.remove_if([&event](const std::unique_ptr<td::event>& __event)
						 {
							 return &__event == &event;
						 });
	}
};

class	event
{
public:
	event() = default;
	virtual ~event() = 0;
};

class	action_event : public event
{
protected:
	action	__action;
public:
	action_event(action action) : __action(action) {  }
	virtual ~action_event() = default;
	inline __attribute__((always_inline))
	const action&	action() const
	{
		return __action;
	}
};

__end_ns_td
