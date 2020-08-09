#pragma once
#ifndef _HYR_ITERATOR_CONTAINER_H
#define _HYR_ITERATOR_CONTAINER_H

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
			std::string m_Name;
			std::string m_Description;

			// To do: Add additional items elements
		};

		class Kitchen
		{
			using Iterator = IteratorBase<Kitchen>;
		public:
			Kitchen()
			{}

			void Emplace(Item& _Item)
			{
				m_Items.emplace_back(_Item);
				return;
			}

			void Emplace(Item&& _Item)
			{
				m_Items.emplace_back(_Item);
				return;
			}

			uint32_t Count()
			{
				return m_Items.size();
			}

			Item GetItems()
			{
				// to be finished
				return m_Items.at(0);
			}
			Iterator begin()
			{
				return Iterator(this, 0);
			}

			Iterator end()
			{
				return Iterator(this, m_Items.size());
			}

		private:
			std::vector<Item> m_Items;;
		};

		template<typename _Cont>
		_Cont& IteratorBase<_Cont>::operator*()
		{
			return *m_Container;
		}
	}
}
#endif // _HYR_ITERATOR_CONTAINER_H