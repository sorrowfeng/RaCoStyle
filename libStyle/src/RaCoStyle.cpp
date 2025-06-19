/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This file is part of Ramses Composer
 * (see https://github.com/bmwcarit/ramses-composer).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "style/RaCoStyle.h"
#include "style/Colors.h"
#include "style/Icons.h"

#include <QApplication>
#include <QComboBox>
#include <QFontDatabase>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QStyleFactory>

namespace raco::style {
RaCoStyle::RaCoStyle() : QProxyStyle(QStyleFactory::create("windows")) {
  setObjectName("RaCoStyle");

  // disable takeover of windows color scheme to make style work
  QApplication::setDesktopSettingsAware(false);
}

QPalette RaCoStyle::standardPalette() const {
  if (!defPalette_.isBrushSet(QPalette::Disabled, QPalette::Mid)) {
    QPalette palette(Colors::color(Colormap::grayBack));

    // set base colors for all color groups
    palette.setBrush(QPalette::Text, Colors::brush(Colormap::text));
    palette.setBrush(QPalette::BrightText, Colors::brush(Colormap::text));
    palette.setBrush(QPalette::Base, Colors::brush(Colormap::grayEdit));
    palette.setBrush(QPalette::Button, Colors::brush(Colormap::grayButton));
    palette.setBrush(QPalette::Highlight, Colors::brush(Colormap::selected));

    // set disabled colors
    palette.setBrush(QPalette::Disabled, QPalette::Text,
                     Colors::color(Colormap::textDisabled));
    palette.setBrush(QPalette::Disabled, QPalette::BrightText,
                     Colors::color(Colormap::textDisabled));
    palette.setBrush(QPalette::Disabled, QPalette::Base,
                     Colors::color(Colormap::grayEditDisabled));
    // button is also used for menu items
    palette.setBrush(QPalette::Disabled, QPalette::Button,
                     Colors::brush(Colormap::grayButton));

    defPalette_ = palette;
  }

  return defPalette_;
}

void RaCoStyle::polish(QWidget* widget) {
  if (qobject_cast<QLineEdit*>(widget)) {
    widget->setAttribute(Qt::WA_OpaquePaintEvent, true);
    widget->setAutoFillBackground(false);
  }
  if (QComboBox* cb = (qobject_cast<QComboBox*>(widget))) {
    cb->setFrame(false);
    cb->setAttribute(Qt::WA_OpaquePaintEvent, true);
  }
  if (QAbstractSpinBox* sb = (qobject_cast<QAbstractSpinBox*>(widget))) {
    sb->setAttribute(Qt::WA_OpaquePaintEvent, true);
    sb->setAutoFillBackground(false);
  }
  if (QPushButton* pb = (qobject_cast<QPushButton*>(widget))) {
    pb->installEventFilter(this);
  }
}

int RaCoStyle::pixelMetric(PixelMetric metric, const QStyleOption* option,
                           const QWidget* widget) const {
  switch (metric) {
    // button margin
    case PM_ButtonMargin:
      return 0;

    // check box size
    case PM_IndicatorHeight:
      return 20;
    case PM_IndicatorWidth:
      return 20;

    case PM_FocusFrameHMargin:
      return 2;
    case PM_DefaultFrameWidth:
      return 0;
    case PM_ScrollBarExtent:
      return 16;
    case PM_ScrollBarSliderMin:
      return 40;
    default:
      return QProxyStyle::pixelMetric(metric, option, widget);
  }
}

int RaCoStyle::styleHint(StyleHint hint, const QStyleOption* option,
                         const QWidget* widget,
                         QStyleHintReturn* returnData) const {
  switch (hint) {
    case SH_DitherDisabledText:
      return int(false);
    case SH_EtchDisabledText:
      return int(false);
    case SH_DockWidget_ButtonsHaveFrame:
      return int(false);
    case SH_ToolTip_WakeUpDelay:
      return 200;
    case SH_ToolTip_FallAsleepDelay:
      return 5000;
    case SH_SpinBox_StepModifier:
      return Qt::ShiftModifier;
    default:
      return QProxyStyle::styleHint(hint, option, widget, returnData);
  }
}

QIcon RaCoStyle::standardIcon(StandardPixmap standardIcon,
                              const QStyleOption* option,
                              const QWidget* widget) const {
  QIcon icon;
  switch (standardIcon) {
    case SP_TitleBarCloseButton:
      return Icons::instance().close;
      break;
    case SP_TitleBarNormalButton:
      return Icons::instance().undock;
      break;
    case SP_TitleBarMenuButton:
      return Icons::instance().menu;
      break;
    default:
      return QProxyStyle::standardIcon(standardIcon, option, widget);
  }
}

QPixmap RaCoStyle::generatedIconPixmap(QIcon::Mode iconMode,
                                       const QPixmap& pixmap,
                                       const QStyleOption* opt) const {
  if (iconMode == QIcon::Mode::Disabled) {
    QPixmap transparentPixmap(pixmap.size());
    transparentPixmap.fill(Qt::transparent);
    QPainter p(&transparentPixmap);
    p.setOpacity(DISABLED_ICON_ALPHA);
    p.drawPixmap(0, 0, pixmap);
    return transparentPixmap;
  }

  return QProxyStyle::generatedIconPixmap(iconMode, pixmap, opt);
}

QRect RaCoStyle::subControlRect(ComplexControl cc,
                                const QStyleOptionComplex* opt, SubControl sc,
                                const QWidget* widget) const {
  return QProxyStyle::subControlRect(cc, opt, sc, widget);
}

QRect RaCoStyle::subElementRect(QStyle::SubElement sr, const QStyleOption* opt,
                                const QWidget* widget) const {
  return QProxyStyle::subElementRect(sr, opt, widget);
}

QSize RaCoStyle::sizeFromContents(ContentsType ct, const QStyleOption* opt,
                                  const QSize& csz,
                                  const QWidget* widget) const {
  return QProxyStyle::sizeFromContents(ct, opt, csz, widget);
}

void RaCoStyle::drawComplexControl(QStyle::ComplexControl control,
                                   const QStyleOptionComplex* option,
                                   QPainter* p, const QWidget* widget) const {
  QProxyStyle::drawComplexControl(control, option, p, widget);
}

void RaCoStyle::drawControl(ControlElement ce, const QStyleOption* opt,
                            QPainter* p, const QWidget* widget) const {
  switch (ce) {
    case CE_PushButton:
      if (const QStyleOptionButton* btn =
              qstyleoption_cast<const QStyleOptionButton*>(opt)) {
        QStyleOptionButton subopt = *btn;
        subopt.rect = subElementRect(SE_PushButtonContents, btn, widget);
        proxy()->drawControl(CE_PushButtonLabel, &subopt, p, widget);
        if (btn->state & State_HasFocus) {
          QStyleOptionFocusRect fropt;
          fropt.QStyleOption::operator=(*btn);
          fropt.rect = subElementRect(SE_PushButtonFocusRect, btn, widget);
          proxy()->drawPrimitive(PE_FrameFocusRect, &fropt, p, widget);
        }
      }
      break;

    case CE_ScrollBarAddPage:
    case CE_ScrollBarSubPage:
      p->setPen(opt->palette.color(QPalette::Base));
      p->setBrush(opt->palette.brush(QPalette::Window));
      p->drawRect(opt->rect);
      break;
    case CE_ScrollBarSlider:
      p->setPen(opt->palette.color(QPalette::Base));
      p->setBrush(opt->palette.brush(QPalette::Button));
      p->drawRect(opt->rect);
      break;
    case CE_ScrollBarSubLine:
    case CE_ScrollBarAddLine: {
      QStyleOption buttonOpt = *opt;

      PrimitiveElement arrow;
      if (opt->state & State_Horizontal) {
        if (ce == CE_ScrollBarAddLine) {
          buttonOpt.rect = opt->rect.adjusted(-10, 1, -1, -1);
          arrow = PE_IndicatorArrowRight;
        } else {
          buttonOpt.rect = opt->rect.adjusted(1, 1, 10, -1);
          arrow = PE_IndicatorArrowLeft;
        }
      } else {
        if (ce == CE_ScrollBarAddLine) {
          buttonOpt.rect = opt->rect.adjusted(1, -10, -1, -1);
          arrow = PE_IndicatorArrowDown;
        } else {
          buttonOpt.rect = opt->rect.adjusted(1, 1, -1, 10);
          arrow = PE_IndicatorArrowUp;
        }
      }
      drawRoundedRect(buttonOpt.rect, p, opt->palette.brush(QPalette::Button),
                      &opt->palette.brush(QPalette::Window));

      QStyleOption arrowOpt = *opt;
      arrowOpt.rect = opt->rect.adjusted(4, 4, -4, -4);
      proxy()->drawPrimitive(arrow, &arrowOpt, p, widget);
      break;
    }
    case CE_ShapedFrame:
      if (widget->objectName() == "dockAreaTitleBar") {
        p->fillRect(opt->rect, Colors::brush(Colormap::dockTitleBackground));
      }
      QProxyStyle::drawControl(ce, opt, p, widget);
      break;
    case CE_DockWidgetTitle:
      if (qstyleoption_cast<const QStyleOptionDockWidget*>(opt)) {
        p->fillRect(opt->rect, Colors::brush(Colormap::dockTitleBackground));
      }
      QProxyStyle::drawControl(ce, opt, p, widget);
      break;
    default:
      QProxyStyle::drawControl(ce, opt, p, widget);
  }
}

void RaCoStyle::drawPrimitive(PrimitiveElement element,
                              const QStyleOption* option, QPainter* p,
                              const QWidget* widget) const {
  switch (element) {
    case PE_PanelLineEdit:
      if (const QStyleOptionFrame* opt =
              qstyleoption_cast<const QStyleOptionFrame*>(option)) {
        QBrush backBrush = opt->palette.brush(QPalette::Base);
        // enlarge box to clip right rounded corners
        QRect bounds(opt->rect);
        if (const QLineEdit* le = qobject_cast<const QLineEdit*>(widget)) {
          if (const QAbstractSpinBox* spin =
                  qobject_cast<const QAbstractSpinBox*>(le->parent())) {
            bounds.adjust(0, 0, 10, 0);
          }
        }
        if (widget->parent() && dynamic_cast<QComboBox*>(widget->parent())) {
          // avoid duplicate rounded border drawing when the lineEdit is a combo box child.
          bounds.adjust(-5, 0, 5, 0);
        }

        drawRoundedRect(bounds, p, backBrush,
                        &opt->palette.brush(QPalette::Window));

        // we don't use a frame in the style, so we don't need to calculate or draw it
      }
      break;

    case PE_IndicatorCheckBox:
      if (const QStyleOptionButton* opt =
              qstyleoption_cast<const QStyleOptionButton*>(option)) {
        QBrush fill;
        if (!(opt->state & State_On) && !(opt->state & State_Off))  // Tristate
          fill = opt->palette.base();
        else if (opt->state & State_NoChange)
          fill = QBrush(opt->palette.base().color(), Qt::Dense4Pattern);
        else if (opt->state & State_Sunken)
          fill = opt->palette.button();
        else if (opt->state & State_Enabled)
          fill = opt->palette.base();
        else
          fill = opt->palette.base();
        p->save();

        drawRoundedRect(opt->rect, p, fill,
                        &opt->palette.brush(QPalette::Window));

        if (opt->state & State_NoChange)
          p->setPen(opt->palette.dark().color());
        else
          p->setPen(opt->palette.text().color());

        if (opt->state & State_On) {
          QPointF points[6];
          qreal scaleh = opt->rect.width() / 12.0;
          qreal scalev = opt->rect.height() / 12.0;
          points[0] = {opt->rect.x() + 3.5 * scaleh,
                       opt->rect.y() + 5.5 * scalev};
          points[1] = {points[0].x(), points[0].y() + 2 * scalev};
          points[2] = {points[1].x() + 2 * scaleh, points[1].y() + 2 * scalev};
          points[3] = {points[2].x() + 4 * scaleh, points[2].y() - 4 * scalev};
          points[4] = {points[3].x(), points[3].y() - 2 * scalev};
          points[5] = {points[4].x() - 4 * scaleh, points[4].y() + 4 * scalev};
          p->setPen(QPen(opt->palette.text().color(), 0));
          p->setBrush(opt->palette.text().color());
          p->drawPolygon(points, 6);
        } else if (!(opt->state & State_On) &&
                   !(opt->state & State_Off)) {  // Tristate
          QPointF points[4];
          qreal scaleh = opt->rect.width() / 12.0;
          qreal scalev = opt->rect.height() / 12.0;
          points[0] = {opt->rect.x() + 3 * scaleh, opt->rect.y() + 5 * scalev};
          points[1] = {points[0].x() + 6 * scaleh, points[0].y() + 0 * scalev};
          points[2] = {points[1].x() + 0 * scaleh, points[1].y() + 2 * scalev};
          points[3] = {points[2].x() - 6 * scaleh, points[2].y() + 0 * scalev};
          p->setPen(QPen(opt->palette.text().color(), 0));
          p->setBrush(opt->palette.text().color());
          p->drawPolygon(points, 4);
        }
        p->restore();
      }
      break;

    case (QStyle::PE_IndicatorItemViewItemDrop): {
      if (!option->rect.isNull()) {
        QStyleOption dragIndicatorRectOption(*option);
        dragIndicatorRectOption.rect.setLeft(0);
        if (widget != nullptr) {
          dragIndicatorRectOption.rect.setRight(
              widget->width() - DRAG_INDICATOR_RIGHT_PIXEL_PUFFER);
        }
        QProxyStyle::drawPrimitive(element, &dragIndicatorRectOption, p,
                                   widget);
      }
      break;
    }

    case PE_IndicatorBranch: {
      static const int decoration_size = 24;
      int mid_h = option->rect.x() + option->rect.width() / 2;
      int mid_v = option->rect.y() + option->rect.height() / 2;
      int bef_h = mid_h;
      int bef_v = mid_v;
      int aft_h = mid_h;
      int aft_v = mid_v;
      if (option->state & State_Children) {
        int delta = decoration_size / 2;
        bef_h -= delta;
        bef_v -= delta;
        aft_h += delta;
        aft_v += delta;
        // draw icons
        if (option->state & State_Open)
          Icons::instance().expanded.paint(
              p, {bef_h, bef_v, decoration_size, decoration_size});
        else
          Icons::instance().collapsed.paint(
              p, {bef_h, bef_v, decoration_size, decoration_size});
      }
      // draw lines, untouched code
      QBrush brush(option->palette.dark().color(), Qt::Dense4Pattern);
      if (option->state & State_Item) {
        if (option->direction == Qt::RightToLeft)
          p->fillRect(option->rect.left(), mid_v, bef_h - option->rect.left(),
                      1, brush);
        else
          p->fillRect(aft_h, mid_v, option->rect.right() - aft_h + 1, 1, brush);
      }
      if (option->state & State_Sibling)
        p->fillRect(mid_h, aft_v, 1, option->rect.bottom() - aft_v + 1, brush);
      if (option->state &
          (State_Open | State_Children | State_Item | State_Sibling))
        p->fillRect(mid_h, option->rect.y(), 1, bef_v - option->rect.y(),
                    brush);
      break;
    }

    default:
      QProxyStyle::drawPrimitive(element, option, p, widget);
  }
}

/**
* Helper method to draw rounded rectangles with uniform corner radius throughout the style. public for use in custom widgets.
*/
void RaCoStyle::drawRoundedRect(const QRect& rect, QPainter* p,
                                const QBrush& fill, const QBrush* clear,
                                const int radius) const {
  // optionally clear background
  if (clear)
    p->fillRect(rect, *clear);

  p->setRenderHint(QPainter::Antialiasing);
  QPainterPath path;
  path.addRoundedRect(rect, radius, radius);
  p->fillPath(path, fill);
}

/**
* Helper method to implement custom behavior in an event filter
*/
bool RaCoStyle::eventFilter(QObject* obj, QEvent* event) {
  // activate hover for push button
  if (QPushButton* pb = (qobject_cast<QPushButton*>(obj))) {
    if (event->type() == QEvent::Enter) {
      pb->setProperty("hoverActive", true);
      pb->update();
      return true;
    } else if (event->type() == QEvent::Leave) {
      pb->setProperty("hoverActive", false);
      pb->update();
      return true;
    }
  }

  return QObject::eventFilter(obj, event);
}
}  // namespace raco::style