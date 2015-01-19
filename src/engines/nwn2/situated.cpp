/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file engines/nwn2/situated.cpp
 *  NWN2 situated object.
 */

#include "common/error.h"
#include "common/maths.h"
#include "common/util.h"

#include "aurora/locstring.h"
#include "aurora/gfffile.h"
#include "aurora/2dafile.h"
#include "aurora/2dareg.h"

#include "graphics/aurora/model.h"

#include "engines/aurora/util.h"
#include "engines/aurora/model.h"

#include "engines/nwn2/situated.h"

namespace Engines {

namespace NWN2 {

Situated::Situated(ObjectType type) : Object(type), _appearanceID(Aurora::kFieldIDInvalid),
	_soundAppType(Aurora::kFieldIDInvalid), _locked(false), _model(0) {

}

Situated::~Situated() {
	delete _model;
}

void Situated::loadModel() {
	if (_model)
		return;

	if (_modelName.empty()) {
		warning("Situated object \"%s\" (\"%s\") has no model", _name.c_str(), _tag.c_str());
		return;
	}

	_model = loadModelObject(_modelName);
	if (!_model)
		throw Common::Exception("Failed to load situated object model \"%s\"",
		                        _modelName.c_str());

	// Positioning

	float x, y, z;

	getPosition(x, y, z);
	setPosition(x, y, z);

	getOrientation(x, y, z);
	setOrientation(x, y, z);

	// Clickable

	_model->setTag(_tag);
	_model->setClickable(isClickable());

	_ids.push_back(_model->getID());
}

void Situated::unloadModel() {
	hide();

	delete _model;
	_model = 0;
}

void Situated::show() {
	if (_model)
		_model->show();
}

void Situated::hide() {
	if (_model)
		_model->hide();
}

void Situated::setPosition(float x, float y, float z) {
	Object::setPosition(x, y, z);
	Object::getPosition(x, y, z);

	if (_model)
		_model->setPosition(x, y, z);
}

void Situated::setOrientation(float x, float y, float z) {
	Object::setOrientation(x, y, z);
	Object::getOrientation(x, y, z);

	if (_model)
		_model->setRotation(x, z, -y);
}

bool Situated::isLocked() const {
	return _locked;
}

void Situated::setLocked(bool locked) {
	_locked = locked;
}

void Situated::load(const Aurora::GFFStruct &instance, const Aurora::GFFStruct *blueprint) {
	// General properties

	if (blueprint)
		loadProperties(*blueprint); // Blueprint
	loadProperties(instance);    // Instance


	// Specialized object properties

	if (blueprint)
		loadObject(*blueprint); // Blueprint
	loadObject(instance);    // Instance


	// Appearance

	if (_appearanceID == Aurora::kFieldIDInvalid)
		throw Common::Exception("Situated object without an appearance");

	loadAppearance();
	loadSounds();


	// Position

	float posX = instance.getDouble("X");
	float posY = instance.getDouble("Y");
	float posZ = instance.getDouble("Z");

	if (instance.hasField("Position")) {
		const Aurora::GFFStruct &pos = instance.getStruct("Position");

		posX = pos.getDouble("x");
		posY = pos.getDouble("y");
		posZ = pos.getDouble("z");
	}

	setPosition(posX, posY, posZ);

	// Orientation

	float bearing = instance.getDouble("Bearing");

	float rotX = 0.0;
	float rotY = Common::rad2deg(bearing);
	float rotZ = 0.0;

	if (instance.hasField("Orientation")) {
		const Aurora::GFFStruct &o = instance.getStruct("Orientation");

		float oX = o.getDouble("x");
		float oY = o.getDouble("y");
		float oZ = o.getDouble("z");
		float oW = o.getDouble("w");

		// Convert quaternions to roll/pitch/yaw
		rotY = 180.0f - Common::rad2deg(atan2(2 * (oX*oY + oZ*oW), 1 - 2 * (oY*oY + oZ*oZ)));
		rotX = 180.0f - Common::rad2deg(asin(2 * (oX*oZ - oW*oY)));
		rotZ = Common::rad2deg(atan2(2 * (oX*oW + oY*oZ), 1 - 2 * (oZ*oZ + oW*oW)));
	}

	setOrientation(rotX, rotY, rotZ);
}

void Situated::loadProperties(const Aurora::GFFStruct &gff) {
	// Tag
	_tag = gff.getString("Tag", _tag);

	// Name
	if (gff.hasField("LocName")) {
		Aurora::LocString name;
		gff.getLocString("LocName", name);

		_name = name.getString();
	}

	// Description
	if (gff.hasField("Description")) {
		Aurora::LocString description;
		gff.getLocString("Description", description);

		_description = description.getString();
	}

	// Appearance
	_appearanceID = gff.getUint("Appearance", _appearanceID);

	// Conversation
	_conversation = gff.getString("Conversation", _conversation);

	// Static
	_static = gff.getBool("Static", _static);

	// Usable
	_usable = gff.getBool("Useable", _usable);

	// Locked
	_locked = gff.getBool("Locked", _locked);
}

void Situated::loadSounds() {
	if (_soundAppType == Aurora::kFieldIDInvalid)
		return;

	const Aurora::TwoDAFile &twoda = TwoDAReg.get("placeableobjsnds");

	_soundOpened    = twoda.getRow(_soundAppType).getString("Opened");
	_soundClosed    = twoda.getRow(_soundAppType).getString("Closed");
	_soundDestroyed = twoda.getRow(_soundAppType).getString("Destroyed");
	_soundUsed      = twoda.getRow(_soundAppType).getString("Used");
	_soundLocked    = twoda.getRow(_soundAppType).getString("Locked");
}

} // End of namespace NWN2

} // End of namespace Engines