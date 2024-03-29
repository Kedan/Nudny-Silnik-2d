#ifndef NUDNY_STATE_H
#define NUDNY_STATE_H

namespace n2d {
	class State {
		public:
			virtual void Enter()	= 0;
			virtual void Exit() 	= 0;			
	};
	
	class EventDrivenState : public State, public Interactive {
		public:
			virtual void Dispatch( sf::Event& ) = 0;

	};
}; // namespace n2d

#endif
