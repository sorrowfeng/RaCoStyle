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

ThemeMode Colors::getThemeMode() {
  return instance().currentThemeMode_;
}

Colors::Colors() noexcept {
  // Dark 主题颜色 (Updated based on Fluent UI dark theme)
  darkColors_ = {// Fluent UI neutralBackground1
                 {Colormap::grayBack, QColor("#202020")},
                 // Fluent UI neutralBackgroundInverted
                 {Colormap::grayEdit, QColor("#121212")},
                 // Fluent UI brandBackground
                 {Colormap::grayButton, QColor("#2F2F2F")},
                 // Fluent UI brandColor
                 {Colormap::selected, QColor("#0078D4")},
                 // Fluent UI neutralForegroundOnColor
                 {Colormap::text, QColor("#FFFFFF")},
                 // Fluent UI neutralBackgroundInvertedDisabled
                 {Colormap::grayEditDisabled, QColor("#181818")},
                 // Fluent UI neutralForegroundDisabled
                 {Colormap::textDisabled, QColor("#A8A8A8")},
                 // Fluent UI neutralBackgroundInverted
                 {Colormap::dockTitleBackground, QColor("#181818")}};

  // Light 主题颜色 (Updated based on Fluent UI light theme)
  lightColors_ = {// Fluent UI neutralBackground
                  {Colormap::grayBack, QColor("#F3F3F3")},
                  // Fluent UI neutralBackgroundInverted
                  {Colormap::grayEdit, QColor("#FFFFFF")},
                  // Fluent UI neutralBackgroundHover
                  {Colormap::grayButton, QColor("#EBEBEB")},
                  // Fluent UI brandColorTinted
                  {Colormap::selected, QColor("#005FA3")},
                  // Fluent UI neutralForeground
                  {Colormap::text, QColor("#000000")},
                  // Fluent UI neutralBackgroundInvertedDisabled
                  {Colormap::grayEditDisabled, QColor("#F8F8F8")},
                  // Fluent UI neutralForegroundDisabled
                  {Colormap::textDisabled, QColor("#9F9F9F")},
                  // Fluent UI neutralBackgroundLighter
                  {Colormap::dockTitleBackground, QColor("#F5F5F5")}};

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