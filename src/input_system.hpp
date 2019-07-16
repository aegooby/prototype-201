
#pragma	once
#include	"__common.hpp"
#include	"system.hpp"

__begin_ns_td

class	input_system : public system
{
public:
	using __base = system;
protected:
public:
	input_system(class world& world) : __base(world)
	{
		flag.set(system::flag::input);
	}
	virtual ~input_system() = default;
	virtual void	update() override {  }
	void	read(class keyboard&, class mouse&);
};

__end_ns_td
