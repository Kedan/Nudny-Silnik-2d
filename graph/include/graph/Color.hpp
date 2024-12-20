#ifndef NUDNY_SILNIK_2D_GRAPH_COLOR_HPP
#define NUDNY_SILNIK_2D_GRAPH_COLOR_HPP

#include <cstdint>
#include <algorithm>
#include <ranges>
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>
#include <tileson/tileson.hpp>

namespace ns {
	template<typename T>
	class Color {
		static_assert(std::is_arithmetic<T>::value,"Color requires a numeric type.");
		public:
			Color(T r=0, T g=0, T b=0, T a=0 ) 
				: m_c( c(r), c(g), c(b), c(a) ){}

			Color(const Color& t_c) 
				: m_c( t_c.m_c){}

			Color(Color&& t_c) noexcept
				: m_c(std::move(t_c.m_c)){}

			explicit Color(sf::Uint32 t_c ) 
				: m_c(t_c){}
			
			explicit Color(const glm::vec3& t_c ) 
				: m_c( f(t_c.x), f(t_c.y), f(t_c.z), i(255)){}

			explicit Color(const glm::vec4& t_c ) 
				: m_c( f(t_c.x), f(t_c.y), f(t_c.z), f(t_c.z)){}

			explicit Color(const sf::Color& c)
				: m_c(c){}
			
			explicit Color(const tson::Colori& c)
				: m_c(c.r, c.g, c.b, c.a ){}

			explicit Color(const std::vector<T>& t_c){
				(*this)(t_c);
			}
			
			explicit Color(const nlohmann::json& t_c) {
				(*this)(t_c);
			}
			
			explicit Color(const std::string& c){
				(*this)(m_c);
			}
		
			// operator ()
			inline sf::Color& operator()(void) {
				return m_c;
			}

			inline Color& operator()( T r, T g, T b, T a ) {
				m_c.r = c(r);
				m_c.g = c(g);
				m_c.b = c(b);
				m_c.a = c(a);
				return *this;
			}

			inline Color& operator()( const Color& c) {
				m_c = c.m_c;
				return *this;
			}

			inline Color& operator()(const glm::vec3& c) {
				m_c.r = f(c.x);
				m_c.g = f(c.y);
				m_c.b = f(c.z);
				m_c.a = i(255);
				return *this;
			}
			
			inline Color& operator()(const glm::vec4& c) {
				m_c.r = f(c.x);
				m_c.g = f(c.y);
				m_c.b = f(c.z);
				m_c.a = f(c.w);
				return *this;
			}
			
			inline Color& operator()(const sf::Color& c) {
				m_c = c;
				return *this;
			}

			inline Color& operator()(sf::Uint32 t_c) {
				m_c = sf::Color(t_c);
				return *this;
			}
			
			inline Color& operator()(const tson::Colori& c) {
				m_c.r = c.r;
				m_c.g = c.g;
				m_c.b = c.b;
				m_c.a = c.a;
				return *this;
			}
			
			inline Color& operator()(const nlohmann::json& c) {
				parseJson(c);
				return *this;
			}
			
			inline Color& operator()(const std::vector<T>&c) {
				if(c.size()>2) {
					m_c.r = c(c[0]);
					m_c.g = c(c[1]);
					m_c.b = c(c[2]);
					if(c.size()>3)
						m_c.a = c(c[3]);
				}
				return *this;
			}

			inline Color& operator()(const std::string& t_c) {
				parseString(t_c);
				return *this;
			}

			// operator =
			inline Color& operator=(const Color& t_c )			{ return (*this)(t_c); }
			inline Color& operator=(const sf::Color& t_c)		{ return (*this)(t_c); }
			inline Color& operator=(sf::Uint32 t_c)				{ return (*this)(t_c); }
			inline Color& operator=(const tson::Colori& t_c )	{ return (*this)(t_c); }
			inline Color& operator=(const nlohmann::json& t_c)	{ return (*this)(t_c); }
			inline Color& operator=(const std::string&  t_c)	{ return (*this)(t_c); }
			inline Color& operator=(const std::vector<T>& t_c)	{ return (*this)(t_c); }
			
			// operator ==
//			inline bool operator==(const Color& t_c) const			{ return m_c == t_c.m_c; }
			inline bool isEqual(const Color& t_c) const				{ return m_c == t_c.m_c; } 
			inline bool operator==(const sf::Color& t_c) const		{ return m_c == t_c; }
			inline bool operator==(uint32_t t_c) const 				{ return m_c == sf::Color(t_c); }
			inline bool operator==(const tson::Colori& t_c) const			{ return isEqual( t_c.r, t_c.g, t_c.b, t_c.a ); }
			bool operator==(const nlohmann::json& t_c) const {
				bool result = false;
				if(isJsonValid(t_c)) {
					result = isEqualJsonComponent(m_c.r, t_c[0])  
							&& isEqualJsonComponent(m_c.g, t_c[1] )
							&& isEqualJsonComponent(m_c.b, t_c[2] );
					if(t_c>3)
							result &= isEqualJsonComponent(m_c.a, t_c[3] );
				}
				return result;
			}
			
			inline bool operator==(const std::string& t_c) const	{ return false; }
			inline bool operator==(const std::vector<T>& t_c) const {
				bool result = false;
				if( t_c.size()>2 ) {
					result = m_c.r == c(t_c[0])
						&& m_c.g == c(t_c[1])
						&& m_c.b == c(t_c[2]);
						if( t_c.size()>3)
							result &= m_c.a == c(t_c[3]);
				}
				throw("std::vector must contains at least 3 elements defining color. Passed parameter defines : "+std::to_string(t_c.size())+".");
			}
			// operator arithmetic
			// setters
			inline void setR(T t_r) { m_c.r = c(t_r); }
			inline void setG(T t_g) { m_c.g = c(t_g); }
			inline void setB(T t_b) { m_c.b = c(t_b); }
			inline void setA(T t_a) { m_c.a = c(t_a); }	
		
			inline void setColor( const Color& t_c ) 			{ (*this)(t_c ); }
			inline void setColor( const sf::Color& t_c ) 		{ (*this)(t_c); }
			inline void setColor( const tson::Color<T>& t_c) 	{ (*this)(t_c); }		
			inline void setColor( const nlohmann::json& t_c) 	{ (*this)(t_c); }		
			inline void setColor( const std::vector<T>& t_c) 	{ (*this)(t_c); }		
			inline void setColor( const std::string& t_c) 		{ (*this)(t_c); }		
			inline void setColor( const glm::vec3& t_c) 		{ (*this)(t_c); }		
			inline void setColor( const glm::vec4& t_c) 		{ (*this)(t_c); }		
			inline void setColor( T r, T g, T b ) 				{ (*this)(r,g,b); }		
			inline void setColor( T r, T g, T b, T a) 			{ (*this)(r, g, b, a); }		
			inline void setColor( uint32_t t_c )				{ (*this)(t_c); }	
				
			// getters
			inline sf::Uint8 getR(T t_r) const { return m_c.r ; }
			inline sf::Uint8 getG(T t_g) const { return m_c.g ; }
			inline sf::Uint8 getB(T t_b) const { return m_c.b ; }
			inline sf::Uint8 getA(T t_a) const { return m_c.a ; }
			
			inline sf::Color 		toSfml()	const { return m_c; }
			inline glm::vec3   	 	toGlm3()	const { return glm::vec3( m_c.r, m_c.g, m_c.b ); }
			inline glm::vec4   	 	toGlm() 	const { return glm::vec4( m_c.r, m_c.g, m_c.b, m_c.a ); }
			inline tson::Colori		toTson()	const { return tson::Colori( m_c.r, m_c.g, m_c.b, m_c.a ); }
			inline std::vector<T>	toVector()	const { return std::vector<T>(m_c.r, m_c.g, m_c.b, m_c.a); }
			inline std::string		toString()	const { return std::string(); }
			inline nlohmann::json	toJson()	const { return nlohmann::json(); }

			static constexpr std::pair<T,T>	getRange() 			{ return m_range; }
		private:
			inline sf::Uint8 c( T c ) 		const { return static_cast<sf::Uint8>( m_factor*std::ranges::clamp(c,m_range.first,m_range.second));}
			inline sf::Uint8 f( float c ) 	const { return static_cast<sf::Uint8>( 255*std::ranges::clamp( c, 0.0f, 1.0f ));	}
			inline sf::Uint8 i( int c ) 	const { return static_cast<sf::Uint8>( std::ranges::clamp( c, 0, 255 ));	}
			
			void parseJson(const nlohmann::json& c) {
				if(isJsonValid(c)){
					m_c.r = c[0].is_number_float() ? f(c[0]) : i(c[0]);
					m_c.r = c[1].is_number_float() ? f(c[1]) : i(c[1]);
					m_c.r = c[2].is_number_float() ? f(c[2]) : i(c[2]);
					if(c.size()>3)
						m_c.r = c[3].is_number_float() ? f(c[3]) : i(c[3]);
				}
				throw std::invalid_argument("JSON must be at least 3-element array, of floating points or integrals.");
			}

			void parseString(const std::string& c) {
			}
			
			inline bool isJsonValid(const nlohmann::json& c) 									const { return c.is_array() && c.size()>=3; }
			inline bool isStringValid(const std::string& c, const std::string t_separator=",") 	const { return false; }
			inline bool isEqual(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) 							const { return m_c.r == r && m_c.g == g && m_c.b == b; }
			inline bool isEqual(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) 			const { return m_c.r == r && m_c.g == g && m_c.b == b && m_c.a == a;}
			inline bool isEqualJsonComponent(sf::Uint8 t_c, const nlohmann::json& t_cc ) 		const {
				if( t_cc.is_number_float() ) {
					return t_c == f(t_cc);
				} else if( t_cc.is_number_integer() ){
					return t_c == c(t_cc);
				}
				throw std::invalid_argument("JSON Color components must be floating point (in range from 0.0f to 1.0f) or integral (from 0 to 255).");
			}
			
			static constexpr std::pair<T,T> setRange() {
				if constexpr (std::is_floating_point<T>::value) {
					return {0.0,1.0};
				} else if constexpr ( std::is_integral<T>::value) {
					return {0,255};
				}
				throw std::domain_error("Color could not estabils range of color values.");
			}

			static constexpr float setFactor() {
				if constexpr (std::is_floating_point<T>::value ) {
					return 255.0f;
				}
				return 1.0f;
			}

		private:
			sf::Color								m_c{255,255,255,255};
			static inline constexpr std::pair<T,T> 	m_range = setRange();
			static inline constexpr float			m_factor = setFactor(); 
	};

	class Colorf : public Color<float>{
		public:
			using Color<float>::operator==;
			using Color<float>::operator=;
			using Color<float>::Color;
	};
	class Colori : public Color<int>{
		public:
			using Color<int>::operator==;
			using Color<int>::operator=;
			using Color<int>::Color;
	};
	
	template<typename T>
	inline bool operator==(const Color<T>& c0, const Color<T>& c1) {
		return c0.isEqual(c1);
	}
};

#endif
