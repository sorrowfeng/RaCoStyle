#include "style/ThemeManager.h"

#include <QApplication>
#include <QStyleFactory>
#include <QWidget>
#include "style/RaCoStyle.h"

namespace raco::style {
ThemeManager& ThemeManager::instance() {
  static ThemeManager inst;
  return inst;
}

void ThemeManager::setThemeMode(ThemeMode mode) {
  Colors::setThemeMode(mode);
  qApp->setStyle(new RaCoStyle());
  qApp->setPalette(qApp->style()->standardPalette());
  emit themeChanged();
}

void ThemeManager::refreshAllWidgets() {
  for (QWidget* widget : qApp->allWidgets()) {
    widget->setStyle(qApp->style());
    widget->update();
  }
}
}  // namespace raco::style