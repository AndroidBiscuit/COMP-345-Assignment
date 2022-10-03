#include "Orders.h"
#include <iostream>
#include<string>
#include <list>
#include <string>
using namespace std;


//-----------------------ORDERS FUNCTION IMPLEMENTATION----------------------//

Order::Order() {
	orderName = "";
}

Order::Order(string x) {
	orderName = x;
}

string Order::getOrderName() { return orderName; }
/*
istream& operator >>(istream& input, Order order) {

}

ostream& operator <<(ostream& input, Order order) {
	cout << "Order is: " << order << endl;

}
*/

//-----------------------DEPLOY FUNCTION IMPLEMENTATION----------------------//
/*
Deploy::Deploy() {
	
}

bool Deploy::validate(string order){
	string deploy = "deploy";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Deploy::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Deploy: put a certain number of army units on a target territory" << endl;
	}
	
}

*/


//----------------------ORDERSLIST FUNCTION IMPLEMENTATION----------------------//

OrdersList::OrdersList() {

}

void OrdersList::addOrder(int a) {
	//alist.push_back(a);
	alist.emplace_back(a);
}

void OrdersList::addOrder(Order* orderToBeAdded)
{
	//Order a = orderToBeAdded;
	 //ordersList.emplace_back(orderToBeAdded);
	//ordersList.insert(ordersList.end(), orderToBeAdded);
	ordersList.push_back(orderToBeAdded);
}

void OrdersList::move(int sourceIndex, int destinationIndex) {
	//sourceIndex - order to be moved from
	//destinationIndex - index order is to be moved to
	list<Order*> tempList;
	list<Order*>::iterator iterator2 = ordersList.begin();
	advance(iterator2, sourceIndex - 1);
	tempList.push_back(*iterator2);
	list<Order*>::iterator iterator1 = ordersList.begin();
	advance(iterator1, destinationIndex - 1);
	ordersList.splice(iterator1, tempList);
	ordersList.erase(iterator2);
}

void OrdersList::remove(int indexOfOrder) {
	list<Order*>::iterator iterator = ordersList.begin();
	advance(iterator, indexOfOrder - 1);
	iterator = ordersList.erase(iterator);

}

void OrdersList::showOrdersList() {
	int index = 1;
	for (auto x : ordersList)
	{
		cout << index << ": " << x->getOrderName() << endl;
		index++;
	}


}