/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This file is part of Ramses Composer
 * (see https://github.com/bmwcarit/ramses-composer).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "style/Colors.h"

namespace raco::style {

QColor& Colors::color(Colormap color) {
  if (instance().currentThemeMode_ == ThemeMode::Dark) {
    return instance().darkColors_[color];
  } else {
    return instance().lightColors_[color];
  }
}

QBrush& Colors::brush(Colormap color) {
  if (instance().currentThemeMode_ == ThemeMode::Dark) {
    return instance().darkBrushes_[color];
  } else {
    return instance().lightBrushes_[color];
  }
}

void Colors::setThemeMode(ThemeMode mode) {
  instance().currentThemeMode_ = mode;
}

Colors::Colors() noexcept {
  // Dark 主题颜色
  darkColors_ = {{Colormap::grayBack, QColor(50, 50, 50)},
                 {Colormap::grayEdit, QColor(20, 20, 20)},
                 {Colormap::grayButton, QColor(90, 90, 90)},
                 {Colormap::selected, QColor(170, 140, 0)},
                 {Colormap::text, QColor(255, 255, 255)},
                 {Colormap::grayEditDisabled, QColor(30, 30, 30)},
                 {Colormap::textDisabled, QColor(200, 200, 200)},

                 //additional colors for text editors
                 {Colormap::textHighlightIndentation, QColor(127, 127, 127)},
                 {Colormap::textHighlightComments, QColor(63, 200, 63)},
                 {Colormap::textHighlightNumbers, QColor(255, 127, 63)},
                 {Colormap::textHighlightArrows, QColor(63, 210, 255)},

                 // additional colors for custom widgets and custom roles/states
                 {Colormap::updatedInBackground, QColor(45, 100, 150)},
                 {Colormap::warningColor, QColor(170, 100, 30)},
                 {Colormap::errorColor, QColor(180, 20, 20)},
                 {Colormap::errorColorDark, QColor(140, 0, 0)},
                 {Colormap::errorColorLight, QColor(255, 120, 120)},
                 {Colormap::dockTitleBackground, QColor(0, 0, 0)},
                 {Colormap::externalReference, QColor(170, 250, 70)},
                 {Colormap::externalReferenceDisabled, QColor(115, 195, 15)},

                 {Colormap::abstractSceneViewBackground, QColor(20, 20, 20)}};

  // Light 主题颜色
  lightColors_ = {{Colormap::grayBack, QColor(248, 248, 248)},
                  {Colormap::grayEdit, Qt::white},
                  {Colormap::grayButton, QColor(230, 230, 230)},
                  {Colormap::selected, QColor(210, 230, 255)},
                  {Colormap::text, Qt::black},
                  {Colormap::grayEditDisabled, QColor(242, 242, 242)},
                  {Colormap::textDisabled, QColor(117, 117, 117)},

                  {Colormap::textHighlightIndentation, QColor(220, 220, 220)},
                  {Colormap::textHighlightComments, QColor(96, 170, 96)},
                  {Colormap::textHighlightNumbers, QColor(255, 130, 0)},
                  {Colormap::textHighlightArrows, QColor(63, 120, 255)},

                  {Colormap::updatedInBackground, QColor(180, 210, 255)},
                  {Colormap::warningColor, QColor(255, 180, 100)},
                  {Colormap::errorColor, QColor(210, 50, 50)},
                  {Colormap::errorColorDark, QColor(190, 30, 30)},
                  {Colormap::errorColorLight, QColor(255, 160, 160)},
                  {Colormap::dockTitleBackground, QColor(240, 240, 240)},
                  {Colormap::externalReference, QColor(160, 200, 100)},
                  {Colormap::externalReferenceDisabled, QColor(130, 160, 80)},
                  {Colormap::abstractSceneViewBackground, Qt::white}};

  for (const auto& [key, value] : darkColors_) {
    darkBrushes_[key] = QBrush(value);
  }
  for (const auto& [key, value] : lightColors_) {
    lightBrushes_[key] = QBrush(value);
  }

  currentThemeMode_ = ThemeMode::Dark;
}

Colors& Colors::instance() {
  if (Colors::instance_ == nullptr) {
    Colors::instance_ = new Colors{};
  }
  return *Colors::instance_;
}

Colors* Colors::instance_{nullptr};

}  // namespace raco::style
