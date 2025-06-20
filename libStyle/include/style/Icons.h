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

#include <QIcon>
#include <QMap>
#include <QPixmap>

namespace raco::style {
typedef QString IconPath;

class Icons {
 public:
  static const Icons& instance();

  QIcon close() const;

  QIcon undock() const;

  QIcon menu() const;

  Icons(const Icons&) = delete;
  Icons& operator=(const Icons&) = delete;

 private:
  Icons();
  ~Icons();

  QMap<QString, QIcon> iconCache_;
};
}  // namespace raco::style
