
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"
#include	"input.hpp"
#include	"event.hpp"
#include	"clock.hpp"
#include	"newton.hpp"
#include	"entity_manager.hpp"
#include	"world.hpp"

__begin_ns_td

class	engine
{
protected:
	window			window;
	keyboard&		keyboard;
	mouse&			mouse;
	clock			clock;
	renderer		renderer;
	newton			newton;
	event_manager	event_manager;
	world			world;
	entity_manager	entity_manager;
	bool		__running = false, __fpsdebug = false;
	const float	__time_per_frame = 1.0f / float(global::game_fps);
protected:
	bool	cmd_w() const;
public:
	engine(const std::string&, int, int, bool);
	~engine() = default;
	void	start();
	void	stop();
	void	render();
	void	update();
	
	//	Preventing copying and moving
	engine(const engine&) = delete;
	engine(engine&&) = delete;
	engine&	operator =(const engine&) = delete;
	engine&	operator =(engine&&) = delete;
};

__end_ns_td
