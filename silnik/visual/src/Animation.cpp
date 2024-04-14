#include "Animation.h"

using namespace n2d;

Frame& Frame::operator=( const Frame& t_frame ) {
	if( this == &t_frame ) {
		return *this;
	}
	duration = t_frame.duration;
	draw_rect = t_frame.draw_rect;
	return *this;
}

void FrameAnimation::Play() {
	m_play = true;
	m_pause = false;
}

void FrameAnimation::Stop() {
	m_play = false;
	m_pause = false;
	m_current_frame = 0;
	m_elapsed_time = 0;
}

void FrameAnimation::Pause() {
	m_pause = true;
}

SpriteAnimation& SpriteAnimation::operator=( const SpriteAnimation& t_animation ) {
	if( this == &t_animation) {
		return *this;
	}
	m_pause 	= t_animation.m_pause;
	m_play		= t_animation.m_play;
	m_elapsed_time 	= t_animation.m_elapsed_time;
	m_current_frame = t_animation.m_current_frame;
	loop		= t_animation.loop;
	speed		= t_animation.speed;
	m_duration	= t_animation.m_duration;
	m_frames	= t_animation.m_frames;
	return *this;
}

SpriteAnimation::SpriteAnimation() {
	loop = true;
	m_duration = 0.0f;
	m_current_frame = 0;
}

SpriteAnimation::SpriteAnimation( sf::Sprite& t_sprite ) {
	mp_sprite = &t_sprite;
	m_duration = 0.0f;
	m_current_frame = 0;
}

void SpriteAnimation::SetSprite( sf::Sprite& t_sprite ) {
	mp_sprite = &t_sprite;
}

void SpriteAnimation::AddFrame( float t_duration, glm::vec4 t_int_rect ) {
	m_frames.push_back(Frame( t_duration, t_int_rect ));
	m_duration += t_duration;
}

void SpriteAnimation::ClearAnimation() {
	m_frames.clear();
	m_duration = 0.0f;
	m_current_frame = 0;
}

void SpriteAnimation::Animate( float t_dt ) {
	if( m_play && !m_pause ) {
		m_elapsed_time += t_dt;
		if( IsTimeElapsed() ) {
			m_elapsed_time = 0;
			NextFrame();
		}
		mp_sprite->setTextureRect( sf::IntRect( 
			m_frames[ m_current_frame ].draw_rect[0], 
			m_frames[ m_current_frame ].draw_rect[1], 
			m_frames[ m_current_frame ].draw_rect[2], 
			m_frames[ m_current_frame ].draw_rect[3] 
		));
	}	
}

void SpriteAnimation::NextFrame() {
	m_current_frame =  m_current_frame >= m_frames.size()-1 ?  0 : m_current_frame+1;
}

void SpriteAnimation::PrevFrame() {
	m_current_frame = m_current_frame <= 0 ? m_frames.size()-1 : m_current_frame-1;
}

bool SpriteAnimation::IsTimeElapsed() {
	return m_elapsed_time > m_frames[ m_current_frame ].duration;
}

void SpriteAnimation::Load( tson::Animation& t_animation, tson::Tileset& t_tileset, glm::vec2 t_map_grid_size ) {
	for( auto frame : t_animation.getFrames() ) {
		int first_GID		= t_tileset.getFirstgid();
		int tile_ID		= frame.getTileId();
		tson::Tile *tile	= t_tileset.getTile( first_GID + tile_ID - 1);
		if( tile ) {
			glm::vec4	draw_rect = Tool::GetDrawingRectG( tile->getDrawingRect(), t_map_grid_size );
			AddFrame( frame.getDuration() * 0.001f, draw_rect );
		} else {
			std::cout << "SpriteAnimation::Load - tile from frame is nullptr\n";
		}
	}
}

int SpriteAnimation::CountFrames() {
	return m_frames.size();
}

float SpriteAnimation::GetDuration() {
	return m_duration;
}
