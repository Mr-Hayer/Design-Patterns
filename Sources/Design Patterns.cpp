// Design Patterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iomanip>
#include "HYR-Observer.h"
#include "HYR-Iterator-Container.h"
#include "HYR-RingBuffer.h"

using namespace HYR::PATTERN;
using namespace HYR::UTILITIES;

void FillBuffer(RingBufferI64& Buffer)
{
    Buffer.PutValue(-23);
    Buffer.PutValue(-25);
    Buffer.PutValue(-27);
    Buffer.PutValue(-29);
    Buffer.PutValue(-31);
    return;
}

void FillBuffer1(RingBufferI64& Buffer)
{
    Buffer.PutValue(-32);
    Buffer.PutValue(-33);
    Buffer.PutValue(-34);
    Buffer.PutValue(-35);
    Buffer.PutValue(-36);
    
    Buffer.PutValue(-25440);
    Buffer.PutValue(-2344);

    return;
}

void GetBuffer(RingBufferI64& Buffer, std::vector<int64_t>& Vector)
{
    while (!Buffer.IsBufferFull());
    Buffer.GetFullBuffer(Vector);
   
    return;
}

int main()
{
	Kitchen MyKitchen(10);
	MyKitchen.Emplace(Item("Door", "Main door to enter in kitchen"));
	MyKitchen.Emplace(Item("Fridge", "Used to keep the food cold"));
	MyKitchen.Emplace(Item("Induction stove", "Used to cook the food"));
	MyKitchen.Emplace(Item("Kitchen base", "Containers to store the long term food"));
	MyKitchen.Emplace(Item("Microwave", "Used to warm the food in short time"));
	std::cout<<"Tot Items: "<<MyKitchen.Count()<<'\n';

    RingBufferI64 Buffer(10);
    std::vector<int64_t> Vector;

    std::thread T1(FillBuffer, std::ref(Buffer));
    std::thread T2(GetBuffer, std::ref(Buffer), std::ref(Vector));
    std::thread T3(FillBuffer1, std::ref(Buffer));

    T1.join();
    T2.join();
    T3.join();


    size_t Idx = 0;
    for (auto const& Itr : Vector) {
        std::cout << "RingBuffer[" << Idx << ']' << Itr << '\n';
        ++Idx;
    }

	for (auto& Itr : MyKitchen)
	{
		std::cout << "Item Name: " << Itr.GetItems()->m_Name.c_str()<<'\n';
		std::cout << "Item Description: " << Itr.GetItems()->m_Description.c_str() << '\n';

	}
}