/*
  Copyright (C) 2014 Jolla Ltd.
  Contact: Slava Monich <slava.monich@jolla.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ClockSettings.h"
#include "ClockDebug.h"

#include <MGConfItem>
#include <QSettings>

#define SETTINGS_GROUP          "Configuration/"
#define DCONF_PATH              "/apps/harbour-swissclock/"
#define KEY_SHOW_NUMBERS        "showNumbers"
#define KEY_INVERT_COLORS       "invertColors"

#define SETTINGS_SHOW_NUMBERS   SETTINGS_GROUP KEY_SHOW_NUMBERS
#define SETTINGS_INVERT_COLORS  SETTINGS_GROUP KEY_INVERT_COLORS
#define DEFAULT_SHOW_NUMBERS    false
#define DEFAULT_INVERT_COLORS   false

ClockSettings::ClockSettings(QObject* aParent) :
    QObject(aParent),
    iShowNumbers(new MGConfItem(DCONF_PATH KEY_SHOW_NUMBERS, this)),
    iInvertColors(new MGConfItem(DCONF_PATH KEY_INVERT_COLORS, this))
{
    QTRACE("- created");

    // Pull in settings from the .ini file
    QSettings settings;
    if (settings.contains(SETTINGS_SHOW_NUMBERS)) {
        bool value = settings.value(SETTINGS_SHOW_NUMBERS).toBool();
        QTRACE("- importing " SETTINGS_SHOW_NUMBERS ":" << value);
        iShowNumbers->set(value);
    }
    if (settings.contains(SETTINGS_INVERT_COLORS)) {
        bool value = settings.value(SETTINGS_INVERT_COLORS).toBool();
        QTRACE("- importing " SETTINGS_INVERT_COLORS ":" << value);
        iInvertColors->set(value);
    }
    settings.remove("");
    settings.sync();

    connect(iShowNumbers, SIGNAL(valueChanged()), SIGNAL(showNumbersChanged()));
    connect(iInvertColors, SIGNAL(valueChanged()), SIGNAL(invertColorsChanged()));
}

ClockSettings::~ClockSettings()
{
    QTRACE("- destroyed");
}

bool ClockSettings::showNumbers() const
{
    return iShowNumbers->value(DEFAULT_SHOW_NUMBERS).toBool();
}

bool ClockSettings::invertColors() const
{
    return iInvertColors->value(DEFAULT_INVERT_COLORS).toBool();
}

void ClockSettings::setShowNumbers(bool aValue)
{
    QTRACE("-" << KEY_SHOW_NUMBERS << "=" << aValue);
    iShowNumbers->set(aValue);
}

void ClockSettings::setInvertColors(bool aValue)
{
    QTRACE("-" << KEY_INVERT_COLORS << "=" << aValue);
    iInvertColors->set(aValue);
}
