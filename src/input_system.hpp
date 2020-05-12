
#pragma	once
#include	"__common.hpp"
#include	"system.hpp"

__begin_ns_td

class	input_system : public system
{
public:
	using __base = system;
protected:
	void	on_down(class entity&);
	void	on_up(class entity&);
public:
	input_system(class world& world) : __base(world)
	{
		flag.set(system::flag::input);
		flag.set(system::flag::state);
	}
	virtual ~input_system() = default;
	virtual void	start() override;
	virtual void	update() override;
	void	on_animation_complete_event(animation_complete_event&);
};

__end_ns_td
