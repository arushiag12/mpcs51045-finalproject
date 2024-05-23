#ifndef REQUESTS_H
#   define REQUESTS_H

#include "basicdefs.h"
#include "orders.h"
#include "orderbook.h"
#include <memory>
#include <type_traits>

using orders::CheckValidOrderType_v;
using orders::OrderTypes;
using orderbook::Orderbook;
namespace requests {


// Base class for all requests
struct Request 
{
    virtual void process(Orderbook& orderbook) = 0;
    virtual ~Request() = default;
};


// Derived classes for different OrderTypes
template <typename OrderType>
requires CheckValidOrderType_v<OrderType, OrderTypes>
struct ValidRequest : public Request 

{
    using type = OrderType;
};


// Add request
template <typename OrderType>
struct AddRequest : public ValidRequest<OrderType>
{
    AddRequest(Side side, Price price, Quantity quantity) 
        : side(side), price(price), quantity(quantity) {}

    void process(Orderbook& orderbook) override {
        orderbook.add<OrderType>(side, price, quantity);
    }

    Side side;
    Price price;
    Quantity quantity;
};
template <typename OrderType>
using AddRequest_t = AddRequest<OrderType>::type;


// Cancel request
template <typename OrderType>
struct CancelRequest : public ValidRequest<OrderType>
{
    CancelRequest(Side side, OrderId id) 
        : side(side), id(id) {}
    
    void process(Orderbook& orderbook) override {
        orderbook.cancel(side, id);
    }

    Side side;
    OrderId id;
};
template <typename OrderType>
using CancelRequest_t = CancelRequest<OrderType>::type;


// Process a request
void processRequest(std::unique_ptr<Request> request, Orderbook& orderbook) {
    request->process(orderbook);
}

}
#endif