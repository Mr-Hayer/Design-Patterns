#pragma once
#ifndef _HYR_ITERATOR_CONTAINER_H
#define _HYR_ITERATOR_CONTAINER_H

#include <exception>
/*
*	@Brief: Iterator to container for "range-based for loop"
*			- Suitable for any Object that impelements begin(), end()
*/
namespace HYR {
	namespace PATTERN {
		template<typename _Cont>
		class IteratorBase
		{
		public:
			IteratorBase(_Cont* Container, uint32_t Pos)
				: m_Container{ Container }, m_Pos{ Pos } {}

			bool operator!=(IteratorBase& _Other)
			{
				return m_Pos == _Other.m_Pos ? false : true;
			}

			IteratorBase& operator++()
			{
				++m_Pos;

				if (m_Container)
					m_Container->SetPosition(m_Pos);

				return *this;
			}

			IteratorBase(IteratorBase&& _Other)
			{
				m_Pos = _Other.m_Pos;
				m_Container = _Other.m_Container;
			}

			_Cont& operator*();

		private:
			uint32_t m_Pos;
			_Cont* m_Container;
		};

		/*
		*	@Brief:	Container example implementing iterator
		*			- Kitchen object as container that can have many items
		*/

		class Item
		{
		public:
			Item() = default;
			Item(std::string _Name, std::string _Description) :
				m_Name(_Name), m_Description(_Description)
			{}

			Item(Item& _Other)
			{
				m_Name = _Other.m_Name;
				m_Description = _Other.m_Description;
			}

			Item(Item&& _Other)
			{
				std::swap(m_Name,_Other.m_Name);
				std::swap(m_Description, _Other.m_Description);
			}
			std::string m_Name;
			std::string m_Description;

			// To do: Add additional items elements
		};

		class Kitchen
		{
			using Iterator = IteratorBase<Kitchen>;
#define MaxSize  100000
		public:
			Kitchen(size_t _TotElements) noexcept(false)
				:
				m_Pos{ 0 },
				m_Elements{_TotElements}
			{
				if (_TotElements > MaxSize)
					throw std::out_of_range("Maximum alloweded elements exeeded");

				// Allocate space
				m_Items = new Item*[_TotElements];
				if (!m_Items)
					throw std::bad_alloc();

				// set *m_Item to nullptr
				for (size_t itr = 0; itr < m_Elements; itr++)
					m_Items[itr] = nullptr;
			}

			~Kitchen()
			{
				// freeing dynamic memory
				while (m_AllocatedElements != 0)
				{
					delete m_Items[m_AllocatedElements];
					m_Items[m_AllocatedElements] = nullptr;
					--m_AllocatedElements;
				}
				delete[] m_Items;
			}

			Item* operator[](size_t _Pos)
			{	// operator to access items as an array
				if (_Pos > m_Elements)
					return nullptr;

				return m_Items[_Pos];
			}

			void Emplace(Item& _Item)
			{
				if (m_AllocatedElements < m_Elements)
				{	// Allocate new item
					Item* TempItem = new Item(_Item);
					m_Items[m_AllocatedElements] = TempItem;
					++m_AllocatedElements;
				}
				return;
			}

			void Emplace(Item&& _Item)
			{
				if (m_AllocatedElements < m_Elements)
				{	// Allocate new item
					Item* TempItem = new Item(_Item);
					m_Items[m_AllocatedElements] = TempItem;
					++m_AllocatedElements;
				}

				return;
			}

			uint32_t Count()
			{
				return m_AllocatedElements;
			}

			Item* GetItems()
			{			
				if (m_Pos > m_Elements)
					return nullptr;

				return m_Items[m_Pos];
			}

			Iterator begin()
			{
				return Iterator(this, 0);
			}

			Iterator end()
			{
				return Iterator(this, m_AllocatedElements);
			}

			void SetPosition(size_t _Pos)
			{
				m_Pos = _Pos;
			}

		private:
			Item** m_Items;
			size_t m_Elements;
			size_t m_AllocatedElements;
			size_t m_Pos;
		};

		template<typename _Cont>
		_Cont& IteratorBase<_Cont>::operator*()
		{
			return *m_Container;
		}
	}
}
#endif // _HYR_ITERATOR_CONTAINER_H