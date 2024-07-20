#ifndef NUDNY_SILNIK_2D_TILED_ENTITY_FACTORY_H
#define NUDNY_SILNIK_2D_TILED_ENTITY_FACTORY_H

#include <tileson/tileson.h>
#include <EntityFactory.h>

namespace nudny {
	class tldEntityFactory : public EntityFactory {
		public:
			tldEntityFactory();
			virtual std::shared_ptr<Entity>	Create( tson::Object& ) = 0;
			std::shared_ptr<Entity> Create();
			void Clear();
		protected:
			std::unique_ptr<tson::Object> m_object;
	}; // class
}; // namespace

#endif
