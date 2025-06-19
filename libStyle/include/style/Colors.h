/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This file is part of Ramses Composer
 * (see https://github.com/bmwcarit/ramses-composer).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include <QBrush>
#include <QColor>
#include <map>

namespace raco::style {

enum class ThemeMode { Dark, Light };

enum class Colormap {
  // standard colors for palette
  grayBack,
  grayEdit,
  grayButton,
  selected,
  text,
  grayEditDisabled,
  textDisabled,

  // additional colors for text editors
  textHighlightIndentation,
  textHighlightComments,
  textHighlightNumbers,
  textHighlightArrows,

  // additional colors for custom widgets and custom roles/states
  updatedInBackground,
  errorColor,
  warningColor,
  errorColorDark,
  errorColorLight,
  dockTitleBackground,
  externalReference,
  externalReferenceDisabled,

  abstractSceneViewBackground
};

class Colors {
 public:
  static QColor& color(Colormap color);
  static QBrush& brush(Colormap color);
  static void setThemeMode(ThemeMode mode);

 private:
  Colors() noexcept;

  static Colors& instance();
  static Colors* instance_;

  std::map<Colormap, QColor> darkColors_;
  std::map<Colormap, QBrush> darkBrushes_;

  std::map<Colormap, QColor> lightColors_;
  std::map<Colormap, QBrush> lightBrushes_;

  ThemeMode currentThemeMode_;
};

}  // namespace raco::style
