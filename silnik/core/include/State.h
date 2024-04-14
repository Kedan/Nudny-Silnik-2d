#ifndef NUDNY_STATE_H
#define NUDNY_STATE_H

namespace n2d {
	/**
	 * Interface. Anstract class.
	 */
	class State {
		public:
			/**
			 * Defines what to do when state is created.
			 * Pre-execute instruction. Check 'State' design pattern for more details.
			 */
			virtual void Enter()	= 0;

			/**
			 * Defines what to do, when state is exiting.
			 * Post-execution instructions. Check 'State' design pattern for more details.
			 */
			virtual void Exit() 	= 0;			
	};
	
	/**
	 * Interface. Anstract class. Keyboard-event driven state. 
	 */
	class EventDrivenState : public State, public Interactive {
		public:
			/**
			 * Check event, and switch to other state if necesery.
			 * @param	- sf::Event handler reference.
			 */
			virtual void Dispatch( sf::Event& ) = 0;

	};
}; // namespace n2d

#endif
