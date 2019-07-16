
#pragma	once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"

__begin_ns_td

class	newton : public system
{
public:
	using __base = system;
protected:
public:
	newton(class world& world) : __base(world)
	{
		__flag.set(system::flag::collision);
		__flag.set(system::flag::transform);
	}
	virtual ~newton() = default;
	inline __attribute__((always_inline))
	void	update(entity_manager&);
};

__end_ns_td
