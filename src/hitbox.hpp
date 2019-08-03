
#pragma	once
#include	"__common.hpp"
#include	"vector.hpp"

__begin_ns_td

struct	hitbox {  };

struct	circle : public hitbox
{
public:
	vector_2	center = vector_2();
	float		radius = 0.0f;
public:
	circle() = default;
	circle(vector_2 center, float radius) : center(center), radius(radius) {  }
	circle(float x, float y, float radius) : center(x, y), radius(radius) {  }
	~circle() = default;
	static bool	check_collision(const circle&, const circle&);
};



__end_ns_td
