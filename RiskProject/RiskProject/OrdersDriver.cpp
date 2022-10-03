#include "Orders.h"
#include "OrdersDriver.h"
#include <iostream>
using namespace std;

void testOrdersLists()
{
	OrdersList ordersList;

	Deploy deploy("deploy");
	Bomb bomb("bomb");
	Advance adv("advance");
	Blockade block("blockade");
	Airlift air("airlift");
	Negotiate neg("negotiate");
	
	ordersList.addOrder(&deploy);
	ordersList.addOrder(&bomb);
	ordersList.addOrder(&adv);
	ordersList.addOrder(&block);
	ordersList.addOrder(&air);
	ordersList.addOrder(&neg);
	cout << "Orders list:" <<"\n";
	ordersList.showOrdersList();
	cout<<"\n";

	//move orders around
	ordersList.move(4, 2);
	cout << "Orders list:" << endl;
	ordersList.showOrdersList();
	cout << "\n";

	//remove an order
	ordersList.remove(3);
	cout << "Orders list:" << endl;
	ordersList.showOrdersList();
	cout << "\n";

	//question about stream insertion operator 
	cout << deploy;
	//deploy.execute(deploy);
	bomb.execute(bomb);
}