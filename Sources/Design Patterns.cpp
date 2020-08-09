// Design Patterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iomanip>
#include "HYR-Observer.h"
#include "HYR-Iterator-Container.h"

using namespace HYR::PATTERN;

int main()
{
	Kitchen MyKitchen;
	MyKitchen.Emplace(Item("Door", "Main door to enter in kitchen"));
	MyKitchen.Emplace(Item("Fridge", "Used to keep the food cold"));
	MyKitchen.Emplace(Item("Induction stove", "Used to cook the food"));
	MyKitchen.Emplace(Item("Kitchen base", "Containers to store the long term food"));
	MyKitchen.Emplace(Item("Microwave", "Used to warm the food in short time"));
	std::cout<<"Tot Items: "<<MyKitchen.Count()<<'\n';

	for (auto& Itr : MyKitchen)
	{
		auto Item = Itr.GetItems();
		std::cout << "Item Name: " << Item.m_Name.c_str()<<'\n';
		std::cout << "Item Description: " << Item.m_Description.c_str() << '\n';
	}
}