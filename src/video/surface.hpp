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

#ifndef HEADER_SUPERTUX_VIDEO_SURFACE_HPP
#define HEADER_SUPERTUX_VIDEO_SURFACE_HPP

#include <string>
#include <boost/optional.hpp>

#include "math/rect.hpp"
#include "math/vector.hpp"
#include "video/flip.hpp"
#include "video/surface_ptr.hpp"
#include "video/texture_ptr.hpp"

class ReaderMapping;
class SurfaceData;

/** A rectangular image.  The class basically holds a reference to a
    texture with additional UV coordinates that specify a rectangular
    area on this texture */
class Surface
{
public:
  static SurfacePtr from_file(const std::string& filename, const boost::optional<Rect>& rect = boost::none);
  static SurfacePtr from_texture(const TexturePtr& texture);
  static SurfacePtr from_reader(const ReaderMapping& mapping,
                                const boost::optional<Rect>& rect = boost::none);

private:
  Surface(const TexturePtr& diffuse_texture, const TexturePtr& displacement_texture,
          const Vector& translate,
          const Vector& scale,
          float rotate,
          const Vector& rotate_center,
          Flip flip);

  Surface(const TexturePtr& diffuse_texture, const TexturePtr& displacement_texture,
          const Rect& region,
          const Vector& translate,
          const Vector& scale,
          float rotate,
          const Vector& rotate_center,
          Flip flip);

public:
  ~Surface();

  SurfacePtr region(const Rect& rect) const;
  SurfacePtr clone(Flip flip = NO_FLIP) const;

  TexturePtr get_texture() const;
  TexturePtr get_displacement_texture() const;
  Rect get_region() const { return m_region; }
  int get_width() const;
  int get_height() const;
  Vector get_translation() const { return m_translate; }
  Vector get_scale() const { return m_scale; }
  float get_rotate() const { return m_rotate; }
  Vector get_rotate_center() const { return m_rotate_center; }
  Flip get_flip() const { return m_flip; }

private:
  const TexturePtr m_diffuse_texture;
  const TexturePtr m_displacement_texture;
  const Rect m_region;
  const Vector m_translate;
  const Vector m_scale;
  const float m_rotate;
  const Vector m_rotate_center;
  const Flip m_flip;

private:
  Surface& operator=(const Surface&) = delete;
};

#endif

/* EOF */
