/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file sound/decoders/wave.h
 *  Decoding RIFF WAVE (Resource Interchange File Format Waveform).
 */

#ifndef SOUND_DECODERS_WAVE_H
#define SOUND_DECODERS_WAVE_H

#include "common/types.h"

namespace Common { class SeekableReadStream; }

namespace Sound {

class RewindableAudioStream;

/**
 * Try to load a WAVE from the given seekable stream and create an AudioStream
 * from that data. Currently this function supports uncompressed
 * raw PCM data, MS IMA ADPCM and MS ADPCM (uses makeADPCMStream internally).
 *
 * @param stream          The SeekableReadStream from which to read the WAVE data.
 * @param disposeAfterUse Whether to delete the stream after use.
 *
 * @return A new RewindableAudioStream, or 0, if an error occured.
 */
RewindableAudioStream *makeWAVStream(
	Common::SeekableReadStream *stream,
	bool disposeAfterUse);

} // End of namespace Sound

#endif // SOUND_DECODERS_WAVE_H
