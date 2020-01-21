/**
 * This file implements methods for play wav files and was based on libsndfile example program.
 \file sndfile-play.cpp
 */


/*
** Copyright (C) 1999-2004 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "sndfile-play.h"


void sndfile_play (const char *file)
{
}

/* sndfile-play.cpp */
// ONLY NEEDS system and audio libs 
// depends on openal and +1

#include <SFML/Audio.hpp>
#include <iostream>
#include "beep.h"

sf::SoundBuffer *sBuffer = NULL;
sf::Sound *bSound = NULL;

void PlayBeepSound()
{
  if (sBuffer == NULL) {
    sBuffer = new sf::SoundBuffer();
    if (!sBuffer->LoadFromSamples((const sf::Int16*)(beep_samples), sizeof(beep_samples)/2, 1, 7418)) {
      fprintf(stderr, "error\n");
      return;
    }
    bSound = new sf::Sound(*sBuffer);
  }
  bSound->Play();
}
