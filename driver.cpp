#include <iostream>
#include <vector>
#include "requests.h"
#include "orderbook.h"
#include "orders.h"
#include "basicdefs.h"
#include "testdata.h"
#include "output.h"

using namespace basicdefs;
using namespace orders;
using namespace orderbook;
using namespace requests;
using namespace testdata;
using namespace output_orderbook;

int main() {
    // Create an orderbook
    Orderbook orderbook;

    // Create a vector of requests
    std::vector<std::unique_ptr<Request>> trades;

    // Generate sample requests
    generate_requests(trades);

    // Process the requests
    for (auto& request : trades) {
        processRequest(move(request), orderbook);
    }

    // Print the orderbook
    std::cout << orderbook;
    return 0;
}
