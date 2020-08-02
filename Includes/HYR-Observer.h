#pragma once

// -Observer.h
#ifndef _HYR_OBSERVER_IMPL_
#define _HYR_OBSERVER_IMPL_

namespace HYR {
	namespace PATTERN {

		class Subject;

		/*
		*	@Brief: Observer update using subject
		*/
		class Observer
		{
		public:
			virtual void Update(Subject&) = 0;
			virtual ~Observer() = default;
		};

		/*
		*	@Brief: A subject has 1..n observers
		*		- It can notify them
		*		- It can attach and detach to/from observer
		*/
		class Subject {
		public:
			virtual ~Subject() = default;
			void Notify();
			void Attach(Observer& obs);
			void Detach(Observer& obs);
		private:
			std::vector<Observer*> observers;
		};	

		void Subject::Attach(Observer& obs)
		{// Subscribe
			observers.push_back(&obs);
		}

		void Subject::Detach(Observer& obs)
		{// Unsubscribe
			observers.erase(std::find(observers.begin(), observers.end(), &obs));
		}

		void Subject::Notify()
		{// Notify observers
			for (auto* Itr : observers)
				Itr->Update(*this);
		}

		/*
		*	@ Brief: Example implementing observer
		*		- Observer1..n implementation
		*		- Inherit from vertual observer class
		*		- Compose Subject to use it inside methods
		*/

		/*
		class observer1: public observer
		{
		public:
			explicit observer1(Subject& S); // ctor
			~observer();

			// To do: Methods

		private:
			Subject& subject;
		}
		*/
	}
}
#endif // _HYR_OBSERVER_IMPL_