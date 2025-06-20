/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This file is part of Ramses Composer
 * (see https://github.com/bmwcarit/ramses-composer).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "style/Icons.h"
#include <QBuffer>
#include <QColor>
#include <QPainter>
#include <QPixmap>
#include <QSvgRenderer>

#include "style/Colors.h"

namespace raco::style {
const Icons& Icons::instance() {
  static Icons icons;
  return icons;
}

Icons::Icons() {}

Icons::~Icons() {}

// 工具函数：从 SVG 字符串生成 QIcon
QIcon iconFromSvgString(const QString& svgData, ThemeMode mode) {
  QSvgRenderer renderer(svgData.toUtf8());

  QPixmap pixmap(32, 32);
  pixmap.fill(Qt::transparent);

  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing, true);

  if (mode == ThemeMode::Light) {
    // 绘制白色图标
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
  }

  renderer.render(&painter);

  painter.end();

  return QIcon(pixmap);
}

// close.svg
static const QString close_svg =
    R"(<svg xmlns="http://www.w3.org/2000/svg" x="0px" y="0px" width="100" height="100" viewBox="0 0 50 50">
<path d="M 7.71875 6.28125 L 6.28125 7.71875 L 23.5625 25 L 6.28125 42.28125 L 7.71875 43.71875 L 25 26.4375 L 42.28125 43.71875 L 43.71875 42.28125 L 26.4375 25 L 43.71875 7.71875 L 42.28125 6.28125 L 25 23.5625 Z"></path>
</svg>)";

QIcon Icons::close() const {
  return iconFromSvgString(close_svg, Colors::getThemeMode());
}

// unlock.svg
static const QString undock_svg =
    R"(<svg t="1750386599089" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="4580" width="200" height="200">
<path d="M810.666667 128H213.333333c-47.061333 0-85.333333 38.272-85.333333 85.333333v597.333334c0 47.061333 38.272 85.333333 85.333333 85.333333h597.333334c47.061333 0 85.333333-38.272 85.333333-85.333333V213.333333c0-47.061333-38.272-85.333333-85.333333-85.333333z m0 85.333333v128H213.333333V213.333333h597.333334zM213.333333 810.666667v-384h597.376l0.042667 384H213.333333z" p-id="4581"></path>
</svg>)";

QIcon Icons::undock() const {
  return iconFromSvgString(undock_svg, Colors::getThemeMode());
}

// menu.svg
static const QString menu_svg =
    R"(<svg xmlns="http://www.w3.org/2000/svg" x="0px" y="0px" width="100" height="100" viewBox="0 0 24 24">
<path d="M 3 5 A 1.0001 1.0001 0 1 0 3 7 L 21 7 A 1.0001 1.0001 0 1 0 21 5 L 3 5 z M 3 11 A 1.0001 1.0001 0 1 0 3 13 L 21 13 A 1.0001 1.0001 0 1 0 21 11 L 3 11 z M 3 17 A 1.0001 1.0001 0 1 0 3 19 L 21 19 A 1.0001 1.0001 0 1 0 21 17 L 3 17 z"></path>
</svg>)";

QIcon Icons::menu() const {
  return iconFromSvgString(menu_svg, Colors::getThemeMode());
}
}  // namespace raco::style