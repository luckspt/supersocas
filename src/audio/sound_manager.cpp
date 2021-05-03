//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "audio/sound_manager.hpp"

#include <wstsound/sound_file.hpp>

#include "audio/sound_source.hpp"
#include "physfs/ifile_stream.hpp"

SoundManager::SoundManager() :
  m_sound_mgr(),
  m_sound_enabled(true),
  m_music_enabled(true)

{
}

void
SoundManager::play(const std::string& name, const Vector& pos, const float gain)
{
  // FIXME: add physfs/cache handling here
  auto sound_file = wstsound::SoundFile::from_stream(std::make_unique<IFileStream>(name));
  auto source = m_sound_mgr.sound().play(std::move(sound_file));
  source->set_position(pos.x, pos.y, 0.0f);
  source->set_gain(gain);
}

void
SoundManager::play(const std::string& name, const float gain)
{
  play(name, Vector(-1, -1), gain);
}

/** preloads a sound, so that you don't get a lag later when playing it */
void
SoundManager::preload(const std::string& name)
{
}

void
SoundManager::play_music(const std::string& filename, float fadetime)
{
  m_music_filename = filename;
}

void
SoundManager::play_music(const std::string& filename, bool fade)
{
  m_music_filename = filename;
}

void
SoundManager::pause_music(float fadetime)
{
  m_sound_mgr.music().pause();
}

void
SoundManager::resume_music(float fadetime)
{
  m_sound_mgr.music().resume();
}

void
SoundManager::stop_music()
{
  m_sound_mgr.music().stop();
}

void
SoundManager::stop_music(float fadetime)
{
  m_sound_mgr.music().stop();
}

std::string
SoundManager::get_current_music() const
{
  return {};
}

void
SoundManager::pause_sounds()
{
  m_sound_mgr.sound().pause();
}

void
SoundManager::resume_sounds()
{
  m_sound_mgr.sound().resume();
}

void
SoundManager::stop_sounds()
{
 m_sound_mgr.sound().stop();
}

void
SoundManager::update()
{
  m_sound_mgr.update(1.0f);
}

std::unique_ptr<SoundSource>
SoundManager::create_sound_source(const std::string& filename)
{
  auto source = m_sound_mgr.create_sound_source(filename, m_sound_mgr.sound(),
                                                wstsound::SoundSourceType::STATIC);
  return std::make_unique<SoundSource>(source);
}

void
SoundManager::set_listener_position(const Vector& position)
{
  m_sound_mgr.set_listener_position(position.x, position.y, -300);
}

void
SoundManager::manage_source(std::unique_ptr<SoundSource> source)
{
}

void
SoundManager::enable_sound(bool sound_enabled)
{
  m_sound_enabled = sound_enabled;
}

void
SoundManager::enable_music(bool music_enabled)
{
  m_music_enabled = music_enabled;
}

void
SoundManager::set_music_volume(int volume)
{
  m_sound_mgr.music().set_gain(static_cast<float>(volume) / 100.0f);
}

void
SoundManager::set_sound_volume(int volume)
{
  m_sound_mgr.sound().set_gain(static_cast<float>(volume) / 100.0f);
}

bool
SoundManager::is_audio_enabled() const
{
  return true;
}

SoundManager& sound_manager()
{
  static SoundManager sound_mgr;
  return sound_mgr;
}

/* EOF */
