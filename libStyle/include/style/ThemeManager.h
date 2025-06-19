#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include "Colors.h"

namespace raco::style {

class ThemeManager : public QObject {
  Q_OBJECT
 public:
  static ThemeManager& instance();

  void setThemeMode(ThemeMode mode);

 Q_SIGNALS:
  void themeChanged();

 private:
  ThemeManager() {}
  ~ThemeManager() {}

  void refreshAllWidgets();
};

}  // namespace raco::style

#endif  // THEMEMANAGER_H
