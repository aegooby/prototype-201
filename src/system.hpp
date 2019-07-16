
#pragma	once
#include	"__common.hpp"
#include	<vector>
#include	<bitset>

__begin_ns_td

class	system_flag : public std::bitset<32>
{
public:
	using __base = std::bitset<32>;
public:
	constexpr system_flag() noexcept = default;
	constexpr system_flag(unsigned long long val) noexcept : __base(val) {  }
	~system_flag() = default;
};

class	system
{
public:
	enum	flag
	{
		unknown = 0x0,
		render = 0x1,
		transform = 0x2,
		collision = 0x3,
		input = 0x4,
		audio = 0x5,
	};
protected:
	std::vector<std::reference_wrapper<entity>>	__registered_entities;
	system_flag		__flag;
	class world&	world;
public:
	system(class world&);
	virtual ~system() = default;
	void	register_entity(class entity&);
	void	deregister_entity(class entity&);
};

__end_ns_td
