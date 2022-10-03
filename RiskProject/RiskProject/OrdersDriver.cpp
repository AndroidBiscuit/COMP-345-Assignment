#include "Orders.h"
#include "OrdersDriver.h"
#include <iostream>
using namespace std;

void testOrdersLists()
{
	OrdersList ordersList;

	Order deploya("deploy-a");
	Order deployb("deploy-b");
	Order deployc("deploy-c");
	Order deployd("deploy-d");
	Order deploye("deploy-e");

	ordersList.addOrder(&deploya);
	ordersList.addOrder(&deployb);
	ordersList.addOrder(&deployc);
	ordersList.addOrder(&deployd);
	ordersList.addOrder(&deploye);
	cout << "Orders list:" << endl;
	ordersList.showOrdersList();
	
	
	ordersList.move(4, 2);
	cout << "Orders list:" << endl;
	ordersList.showOrdersList();
}