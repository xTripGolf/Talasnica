#include <iostream>

#include "talasnica.h"
#include "OrdersManager.h"
#include "Order.h"
#include "OrdersPacket.h"


std::ostream& Talasnica::Exception::operator<<(std::ostream &os, const Talasnica::Exception::Exception &e);
std::ostream& Talasnica::operator<<(std::ostream &os, const Talasnica::Order &order);
std::ostream& Talasnica::operator<<(std::ostream &os, Talasnica::OrdersManager &ordersManager);
std::ostream& Talasnica::operator<<(std::ostream &os, const Talasnica::OrdersPacket &packet);
