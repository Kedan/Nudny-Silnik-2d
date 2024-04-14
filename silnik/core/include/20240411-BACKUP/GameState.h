#ifndef NUDNY_SILNIK_GAME_STATE_H
#define NUDNY_SILNIK_GAME_STATE_H

/**
 * Uwaga fajna mysl!
 * Kolejke stanow gry (scenariusz) zapisac w pliku .json!
 *
 */

#include "State.h"

namespace n2d {
	class Game;

	class GameStateFactory;

	class GameState : 
		public State, 
		public Drawable, 
		public Updatable, 
		public Interactive {
		protected:
			int			m_id;
			json			m_conf;
			GameStateFactory*	mp_factory;
		public:
			b2World			world;
			Resources		src;
		public:
			virtual GameState*	Dispatch( sf::Event& ) 		= 0;
			virtual void		Reset()				= 0;
			virtual void 		Load( json& t_conf )		= 0;	
	//		virtual	void		Create() 			= 0;
	//		virtual void 		Update( float ) 		= 0;
	//		virtual void		Draw( sf::RenderWindow& )	= 0;
	//		virtual void 		Events( sf::Event& ) 		= 0;
	//		virtual	void		Enter() 			= 0;
	//		virtual void		Exit()	 			= 0;
				void		SetGameStateFactory( GameStateFactory& t_factory );
		protected:
			GameState*		GetNextGameState();
	};
	
	// proste, interaktywne animacje
	// fade in, wyswietlenia, oczekiwanie na reakcje, lub uplyw czasu, fade out
	// nastepny stan
	class GameStateLogo : public GameState {
		public:
			GameStateLogo(){};
			GameState*	Dispatch( sf::Event& );
			void 		Update( float );
			void		Draw( sf::RenderWindow& );
			void		Draw( sf::RenderWindow&, sf::Transform& );
			void 		Events( sf::Event& );
			void		Enter();
			void		Exit();
		public:
			bool		IsTimeElapsed();
	};
	
	// stan posredni wyswiatlany gdy laduje sie stan "glowny"
	// fade in, pokaz cos malego fajnego, jak zaladuje sie to co chcemy, fade out
	// pokaz zaladowany stan
	class GameStateLoader : public GameState {
	};

	// mocno interaktywny stan. 
	// jak zbudowac/zaimplementowac menu?
	// sterowanie silnikiem
	class GameStateMainMenu : public GameState {
	};

	// prosty stan - wyswieltanie mpg
	// interaktwywny na Esc
	class GameStateCinematic : public GameState {
	};

	// Wlasciwa gra. Gameplay
	// Tu sie dzieje magja
	class GameStatePlay : public GameState {
	};

	// wyswietlanie literek
	class GameStateCredits : public GameState {
	};	
}; // namespace n2d

#endif 
