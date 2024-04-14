#ifndef _FLUXCPP_STORE_HPP_
#define _FLUXCPP_STORE_HPP_

#include <list>
#include <functional>

#include "fluxcpp/action.hpp"

namespace fluxcpp
{

struct IStoreContainer
{
    virtual void Dispatch(std::shared_ptr<IActionPayload> payload) = 0;
};

template<typename T>
class StoreContainer : public IStoreContainer
{
public:
    void Listen(std::function<void(T*)> handler)
    {
    }

    virtual void Dispatch(std::shared_ptr<IActionPayload> payload)
    {
    }

private:
    std::list<std::function<void(T*)> > _handlers;
};

} // end of namespace fluxcpp
#endif // _FLUXCPP_STORE_HPP_