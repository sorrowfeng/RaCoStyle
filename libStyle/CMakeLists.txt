#[[
SPDX-License-Identifier: MPL-2.0

This file is part of Ramses Composer
(see https://github.com/bmwcarit/ramses-composer).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
]]


add_library(libStyle 
    include/style/Colors.h src/Colors.cpp
    include/style/Icons.h src/Icons.cpp
    include/style/RaCoStyle.h src/RaCoStyle.cpp
    include/style/ThemeManager.h
    src/ThemeManager.cpp
)

target_include_directories(libStyle
    PUBLIC
        include/
)

target_link_libraries(libStyle
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
)
add_library(raco::Style ALIAS libStyle)
