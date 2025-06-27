#include "style/ThemeManager.h"

#include <QApplication>
#include <QSettings>
#include <QStyleFactory>
#include <QStyleHints>
#include <QWidget>
#include "style/RaCoStyle.h"

namespace raco::style {
ThemeManager& ThemeManager::instance() {
  static ThemeManager inst;
  return inst;
}

ThemeMode ThemeManager::getThemeMode() const {
  return Colors::getThemeMode();
}

void ThemeManager::setThemeMode(ThemeMode mode) {
  if (mode == Colors::getThemeMode())
    return;
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

ThemeMode ThemeManager::getSystemThemeMode() const {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
  const auto scheme = QGuiApplication::styleHints()->colorScheme();
  return scheme == Qt::ColorScheme::Dark ? raco::style::ThemeMode::Dark
                                         : raco::style::ThemeMode::Light;
#else
#ifdef Q_OS_WIN
  QSettings m_colorSchemeSettings{
      QSettings::UserScope, "Microsoft",
      "Windows\\CurrentVersion\\Themes\\Personalize"};
  return !m_colorSchemeSettings.value("AppsUseLightTheme").toBool()
             ? raco::style::ThemeMode::Dark
             : raco::style::ThemeMode::Light;
#else   //linux
  const QPalette defaultPalette;
  const auto text = defaultPalette.color(QPalette::WindowText);
  const auto window = defaultPalette.color(QPalette::Window);
  return text.lightness() > window.lightness() ? raco::style::ThemeMode::Dark
                                               : raco::style::ThemeMode::Light;
#endif  // Q_OS_WIN
#endif  // QT_VERSION
}
}  // namespace raco::style
