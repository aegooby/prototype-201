
#pragma	once
#include	"__common.hpp"
#include	"input_enum.hpp"
#include	"array.hpp"
#include	"vector.hpp"

__begin_ns_td

class	window;

KEY_ENUM();
MOUSE_ENUM();

class	input
{
protected:
	window&	window_context;
public:
	input(window& window_context) : window_context(window_context) {  }
	~input() = default;
	
	//	Preventing copying and moving
	input(const input&) = delete;
	input(const input&&) = delete;
	input&	operator=(const input&) = delete;
	input&	operator=(const input&&) = delete;
};

class	keyboard : public input
{
protected:
	array<bool, size_t(keycode::SIZE)>	scan;
	array<bool, size_t(keycode::SIZE)>	down;
	array<bool, size_t(keycode::SIZE)>	up;
	
public:
	keyboard(window& window_context) : input(window_context)
	{
		scan.fill(false);
		down.fill(false);
		up.fill(false);
	}
	~keyboard()
	{
		scan.fill(false);
		down.fill(false);
		up.fill(false);
	}
	inline __attribute__((always_inline))
	bool	key_scan(keycode code) const	{ return scan[size_t(code)]; }
	inline __attribute__((always_inline))
	bool	key_down(keycode code) const	{ return down[size_t(code)]; }
	inline __attribute__((always_inline))
	bool	key_up(keycode code)	const	{ return up[size_t(code)]; }
	inline __attribute__((always_inline))
	void	key_scan(keycode code, bool value)	{ scan[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	key_down(keycode code, bool value)	{ down[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	key_up(keycode code, bool value)		{ up[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	key_scan_clear()	{ scan.fill(false); }
	inline __attribute__((always_inline))
	void	key_down_clear()	{ down.fill(false); }
	inline __attribute__((always_inline))
	void	key_up_clear()		{ up.fill(false); }
	
	//	Preventing copying and moving
	keyboard(const keyboard&) = delete;
	keyboard(const keyboard&&) = delete;
	keyboard&	operator=(const keyboard&) = delete;
	keyboard&	operator=(const keyboard&&) = delete;
};

class	mouse : public input
{
protected:
	array<bool, size_t(mousecode::SIZE)>	scan;
	array<bool, size_t(mousecode::SIZE)>	down;
	array<bool, size_t(mousecode::SIZE)>	up;
	vector_2						__position;
	vector_2						__movement;
public:
	mouse(window& window_context) : input(window_context)
	{
		scan.fill(false);
		down.fill(false);
		up.fill(false);
	}
	~mouse()
	{
		scan.fill(false);
		down.fill(false);
		up.fill(false);
	}
	inline __attribute__((always_inline))
	bool	button_scan(mousecode code) const	{ return scan[size_t(code)]; }
	inline __attribute__((always_inline))
	bool	button_down(mousecode code) const	{ return down[size_t(code)]; }
	inline __attribute__((always_inline))
	bool	button_up(mousecode code)	const	{ return up[size_t(code)]; }
	inline __attribute__((always_inline))
	void	button_scan(mousecode code, bool value)	{ scan[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	button_down(mousecode code, bool value)	{ down[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	button_up(mousecode code, bool value)		{ up[size_t(code)] = value; }
	inline __attribute__((always_inline))
	void	button_scan_clear()	{ scan.fill(false); }
	inline __attribute__((always_inline))
	void	button_down_clear()	{ down.fill(false); }
	inline __attribute__((always_inline))
	void	button_up_clear()		{ up.fill(false); }
	inline __attribute__((always_inline))
	void	visible(bool visible) { SDL_ShowCursor(int(visible)); }
	inline __attribute__((always_inline))
	vector_2	position() const	{ return __position; }
	inline __attribute__((always_inline))
	vector_2	movement() const	{ return __movement; }
	inline __attribute__((always_inline))
	bool	visible() const	{ return SDL_ShowCursor(-1); }
	void	position(float x, float y);
	void	position(const vector_2&);
	void	update()
	{
		int	x, y;
		int	dx, dy;
		SDL_GetMouseState(&x, &y);
		SDL_GetRelativeMouseState(&dx, &dy);
		__position.x(float(x));
		__position.y(float(y));
		__movement.x(float(dx));
		__movement.y(float(dy));
	}
	
	//	Preventing copying and moving
	mouse(const mouse&) = delete;
	mouse(const mouse&&) = delete;
	mouse&	operator=(const mouse&) = delete;
	mouse&	operator=(const mouse&&) = delete;
};

__end_ns_td
