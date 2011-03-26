/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010-2011 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file engines/nwn/gui/options/sound.cpp
 *  The NWN sound options menu.
 */

#include "common/configman.h"

#include "sound/sound.h"

#include "engines/nwn/gui/widgets/panel.h"
#include "engines/nwn/gui/widgets/label.h"
#include "engines/nwn/gui/widgets/slider.h"

#include "engines/nwn/gui/options/sound.h"
#include "engines/nwn/gui/options/soundadv.h"

namespace Engines {

namespace NWN {

OptionsSoundMenu::OptionsSoundMenu(bool isMain) {
	load("options_sound");

	if (isMain) {
		WidgetPanel *backdrop = new WidgetPanel(*this, "PNL_MAINMENU", "pnl_mainmenu");
		backdrop->setPosition(0.0, 0.0, 100.0);
		addWidget(backdrop);
	}

	std::list<Widget *> speakerGroup;
	speakerGroup.push_back(getWidget("71Speakers"));
	speakerGroup.push_back(getWidget("51Speakers"));
	speakerGroup.push_back(getWidget("2Speakers"));
	speakerGroup.push_back(getWidget("4Speakers"));
	speakerGroup.push_back(getWidget("Surround"));
	speakerGroup.push_back(getWidget("Headphones"));
	declareGroup(speakerGroup);

	// TODO: Sound settings
	Widget *soundEAX        = getWidget("EAXCheckbox");
	if (soundEAX)
		soundEAX->setDisabled(true);
	Widget *soundHardware   = getWidget("HardwareBox");
	if (soundHardware)
		soundHardware->setDisabled(true);
	Widget *sound71Speakers = getWidget("71Speakers");
	if (sound71Speakers)
		sound71Speakers->setDisabled(true);
	Widget *sound51Speakers = getWidget("51Speakers");
	if (sound51Speakers)
		sound51Speakers->setDisabled(true);
	Widget *sound4Speakers  = getWidget("4Speakers");
	if (sound4Speakers)
		sound4Speakers->setDisabled(true);
	Widget *sound2Speakers  = getWidget("2Speakers");
	if (sound2Speakers)
		sound2Speakers->setDisabled(true);
	Widget *soundSurround   = getWidget("Surround");
	if (soundSurround)
		soundSurround->setDisabled(true);
	Widget *soundHeadphones = getWidget("Headphones");
	if (soundHeadphones)
		soundHeadphones->setDisabled(true);

	_advanced = new OptionsSoundAdvancedMenu(isMain);
}

void OptionsSoundMenu::show() {
	_volMusic = ConfigMan.getDouble("volume_music", 1.0);
	_volSFX   = ConfigMan.getDouble("volume_sfx"  , 1.0);
	_volVoice = ConfigMan.getDouble("volume_voice", 1.0);
	_volVideo = ConfigMan.getDouble("volume_video", 1.0);

	updateVolume(_volMusic, Sound::kSoundTypeMusic, "MusicLabel");
	updateVolume(_volSFX  , Sound::kSoundTypeSFX  , "SoundFXLabel");
	updateVolume(_volVoice, Sound::kSoundTypeVoice, "VoicesLabel");

	getSlider("MusicSlider"  , true)->setState(_volMusic * 20);
	getSlider("SoundFXSlider", true)->setState(_volSFX   * 20);
	getSlider("VoicesSlider" , true)->setState(_volVoice * 20);

	GUI::show();
}

OptionsSoundMenu::~OptionsSoundMenu() {
	delete _advanced;
}

void OptionsSoundMenu::initWidget(Widget &widget) {
	if (widget.getTag() == "MusicSlider") {
		dynamic_cast<WidgetSlider &>(widget).setSteps(20);
		return;
	}

	if (widget.getTag() == "VoicesSlider") {
		dynamic_cast<WidgetSlider &>(widget).setSteps(20);
		return;
	}

	if (widget.getTag() == "SoundFXSlider") {
		dynamic_cast<WidgetSlider &>(widget).setSteps(20);
		return;
	}
}

void OptionsSoundMenu::callbackActive(Widget &widget) {
	if ((widget.getTag() == "CancelButton") ||
	    (widget.getTag() == "XButton")) {

		revertChanges();
		_returnCode = 1;
		return;
	}

	if (widget.getTag() == "OkButton") {

		adoptChanges();
		_returnCode = 2;
		return;
	}

	if (widget.getTag() == "AdvSoundBtn") {
		sub(*_advanced);
		return;
	}

	if (widget.getTag() == "MusicSlider") {
		_volMusic = dynamic_cast<WidgetSlider &>(widget).getState() / 20.0;
		updateVolume(_volMusic, Sound::kSoundTypeMusic, "MusicLabel");
		return;
	}

	if (widget.getTag() == "VoicesSlider") {
		_volVoice = dynamic_cast<WidgetSlider &>(widget).getState() / 20.0;
		updateVolume(_volVoice, Sound::kSoundTypeVoice, "VoicesLabel");
		return;
	}

	if (widget.getTag() == "SoundFXSlider") {
		_volSFX = _volVideo = dynamic_cast<WidgetSlider &>(widget).getState() / 20.0;
		updateVolume(_volSFX  , Sound::kSoundTypeSFX  , "SoundFXLabel");
		updateVolume(_volVideo, Sound::kSoundTypeVideo, "");
		return;
	}
}

void OptionsSoundMenu::updateVolume(double volume, Sound::SoundType type,
                                    const Common::UString &label) {

	SoundMan.setTypeGain(type, volume);

	if (!label.empty())
		getLabel(label, true)->setText(Common::UString::sprintf("%.0f%%", volume * 100.0));
}

void OptionsSoundMenu::adoptChanges() {
	ConfigMan.setDouble("volume_music", _volMusic, true);
	ConfigMan.setDouble("volume_sfx"  , _volSFX  , true);
	ConfigMan.setDouble("volume_voice", _volVoice, true);
	ConfigMan.setDouble("volume_video", _volVideo, true);
}

void OptionsSoundMenu::revertChanges() {
	SoundMan.setTypeGain(Sound::kSoundTypeMusic, ConfigMan.getDouble("volume_music", 1.0));
	SoundMan.setTypeGain(Sound::kSoundTypeSFX  , ConfigMan.getDouble("volume_sfx"  , 1.0));
	SoundMan.setTypeGain(Sound::kSoundTypeVoice, ConfigMan.getDouble("volume_voice", 1.0));
	SoundMan.setTypeGain(Sound::kSoundTypeVideo, ConfigMan.getDouble("volume_video", 1.0));
}

} // End of namespace NWN

} // End of namespace Engines