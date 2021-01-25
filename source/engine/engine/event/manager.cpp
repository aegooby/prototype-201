
#include "manager.hpp"

namespace p201
{
namespace events
{
function_handler::~function_handler() = default;
void function_handler::exec(std::unique_ptr<event>&& event)
{
    call(std::forward<std::unique_ptr<class event>>(event));
}
} // namespace events
} // namespace p201
