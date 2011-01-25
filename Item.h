#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(std::string itemName, int weight):m_itemName(itemName), m_weight(weight)
	{}
	// returns the itemName of the item
	std::string GetItemName();

	// returns the weight of the item
	int GetWeight();
private:
	std::string m_itemName;
	int m_weight;
};

#endif