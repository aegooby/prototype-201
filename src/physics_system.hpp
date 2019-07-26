
#pragma	once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"

__begin_ns_td

class	physics_system : public system
{
public:
	using __base = system;
protected:
public:
	physics_system(class world& world) : __base(world)
	{
		flag.set(system::flag::collision);
		flag.set(system::flag::transform);
	}
	virtual ~physics_system() = default;
	virtual void	start() override;
	virtual void	update() override;
};

__end_ns_td
