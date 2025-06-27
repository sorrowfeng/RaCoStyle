# RaCoStyle

[![License: MPL-2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://www.mozilla.org/MPL/2.0/)

> 本项目是基于 [Ramses Composer](https://github.com/bmwcarit/ramses-composer) 修改的衍生版本，提取了其中的样式部分, 可用于快速给项目设置Dark/Light模式

## 📌 项目特色

- ✨ **界面风格**：快速切换Dark和Light模式

## ⚙️ 安装与使用

### 依赖项
- Qt 5.15+ 或 Qt 6
- CMake 3.12+

### 效果预览

![250627102851456.png](https://fastly.jsdelivr.net/gh/sorrowfeng/ImageHub@main/2025-06/250627102851456_1750991331477.png)

![250627102919777.png](https://fastly.jsdelivr.net/gh/sorrowfeng/ImageHub@main/2025-06/250627102919777_1750991359785.png)

### 使用说明
```bash
git clone https://github.com/sorrowfeng/RaCoStyle.git

clone到你的项目中
```

```cmake
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

# 添加子目录
add_subdirectory(RaCoStyle/libStyle)

add_executable(${ProjectName} main.cpp)

# 链接库
target_link_libraries(DemoQt6CMake PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
)
target_link_libraries(${ProjectName} PRIVATE
    raco::Style
)
```

```cpp
# 使用
#include "style/RaCoStyle.h"
#include "style/ThemeManager.h"

int main(int argc, char *argv[])
{
  // 默认Dark颜色
  QApplication::setStyle(new raco::style::RaCoStyle());

  QApplication a(argc, argv);

  // force use of style palette, required on Linux
  a.setPalette(a.style()->standardPalette());

  MainWindow w;
  w.show();

  // 在代码中动态切换配色主题
  raco::style::ThemeManager::instance().setThemeMode(
      raco::style::ThemeMode::Light);


  return a.exec();
}

```