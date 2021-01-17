
#pragma once
#include "event.hpp"

#include <__common.hpp>

/**
 * @brief Don't worry too much about how the shit in this file works because
 *        frankly I have no fucking idea either.
 */

namespace p201
{
namespace events
{
class function_handler
{
protected:
    virtual void call(std::unique_ptr<event>&& event) = 0;

public:
    virtual ~function_handler() = 0;
    virtual void exec(std::unique_ptr<event>&& event);
};

template<typename system_type, typename event_type>
class function_handler_template : public function_handler
{
public:
    using event_t  = event_type;
    using system_t = system_type;
    typedef void (system_t::*function_t)(event_t&);

private:
    system_t&  __system;
    function_t __function;

protected:
    virtual void call(std::unique_ptr<event>&& event) override
    {
        (__system.*__function)(*static_cast<event_t*>(event.get()));
    }

public:
    function_handler_template(system_t& system, function_t function)
        : __system(system), __function(function)
    { }
    virtual ~function_handler_template() override = default;
};

class manager
{
public:
    using list_t = std::list<std::unique_ptr<function_handler>>;

protected:
    std::unordered_map<std::type_index, std::unique_ptr<list_t>> __subscribers;
    class world&                                                 world;

public:
    manager(class world& world) : world(world) { }
    ~manager() = default;
    template<typename event_type, typename... types>
    void publish(types&&... args)
    {
        using std::forward;
        using std::make_unique;
        auto& handlers = __subscribers.at(typeid(event_type));
        if (!handlers) return;
        for (auto& handler : *handlers)
        {
            if (handler)
                handler->exec(make_unique<event_type>(forward<types>(args)...));
        }
    }
    template<typename system_type, typename event_type>
    void subscribe(system_type& system,
                   void (system_type::*function)(event_type&))
    {
        using fht_t = function_handler_template<system_type, event_type>;
        constexpr auto& unique_list = std::make_unique<list_t>;
        if (!__subscribers.count(typeid(event_type)))
            __subscribers.emplace(typeid(event_type), unique_list());
        auto& handlers = __subscribers.at(typeid(event_type));
        handlers->emplace_back(std::make_unique<fht_t>(system, function));
    }
};
} // namespace events

} // namespace p201
