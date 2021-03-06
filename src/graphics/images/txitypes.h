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

/** @file graphics/images/txitypes.h
 *  Texture information types.
 */

#ifndef GRAPHICS_IMAGES_TXITYPES_H
#define GRAPHICS_IMAGES_TXITYPES_H

#include "common/util.h"

namespace Common {
	class UString;
}

namespace Graphics {

/** All supported commands in a TXI. */
enum TXICommand {
	TXICommandAlphaMean           =  0,
	TXICommandArturoHeight        =  1,
	TXICommandArturoWidth         =  2,
	TXICommandBaselineHeight      =  3,
	TXICommandBlending            =  4,
	TXICommandBumpMapScaling      =  5,
	TXICommandBumpMapTexture      =  6,
	TXICommandBumpyShinyTexture   =  7,
	TXICommandCanDownsample       =  8,
	TXICommandCaretIndent         =  9,
	TXICommandChannelScale        = 10,
	TXICommandChannelTranslate    = 11,
	TXICommandClamp               = 12,
	TXICommandCodepage            = 13,
	TXICommandCols                = 14,
	TXICommandCompressTexture     = 15,
	TXICommandControllerScript    = 16,
	TXICommandCube                = 17,
	TXICommandDBMapping           = 18,
	TXICommandDecal               = 19,
	TXICommandDefaultBPP          = 20,
	TXICommandDefaultHeight       = 21,
	TXICommandDefaultWidth        = 22,
	TXICommandDistort             = 23,
	TXICommandDistortAngle        = 24,
	TXICommandDistortionAmplitude = 25,
	TXICommandDownsampleFactor    = 26,
	TXICommandDownsampleMax       = 27,
	TXICommandDownsampleMin       = 28,
	TXICommandEnvMapTexture       = 29,
	TXICommandFileRange           = 30,
	TXICommandFilter              = 31,
	TXICommandFontHeight          = 32,
	TXICommandFontWidth           = 33,
	TXICommandFPS                 = 34,
	TXICommandIsBumpMap           = 35,
	TXICommandIsDoubleByte        = 36,
	TXICommandIsLightMap          = 37,
	TXICommandLowerRightCoords    = 38,
	TXICommandMaxSizeHQ           = 39,
	TXICommandMaxSizeLQ           = 40,
	TXICommandMinSizeHQ           = 41,
	TXICommandMinSizeLQ           = 42,
	TXICommandMipMap              = 43,
	TXICommandNumChars            = 44,
	TXICommandNumCharsPerSheet    = 45,
	TXICommandNumX                = 46,
	TXICommandNumY                = 47,
	TXICommandOnDemand            = 48,
	TXICommandPriority            = 49,
	TXICommandProcedureType       = 50,
	TXICommandRows                = 51,
	TXICommandSpacingB            = 52,
	TXICommandSpacingR            = 53,
	TXICommandSpeed               = 54,
	TXICommandTemporary           = 55,
	TXICommandTextureWidth        = 56,
	TXICommandUnique              = 57,
	TXICommandUpperLeftCoords     = 58,
	TXICommandWaterHeight         = 59,
	TXICommandWaterWidth          = 60,
	TXICommandXBoxDownsample      = 61
};

/** Parse a TXI command from a string. */
TXICommand parseTXICommand(const Common::UString &str, int &skip);

} // End of namespace Graphics

#endif // GRAPHICS_IMAGES_TXITYPES_H
