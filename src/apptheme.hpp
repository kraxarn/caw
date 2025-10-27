#pragma once

#include <QRgb>
#include <QtQml>

/*
 * Oil 6 Palette
 * By GrafxKid
 * https://lospec.com/palette-list/oil-6
 */

class AppTheme final: public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString windowText READ windowText NOTIFY windowTextChanged)

public:
	explicit AppTheme(QObject *parent = nullptr);

	static void setStyle();

	[[nodiscard]]
	static auto qmlAttachedProperties(QObject *object) -> AppTheme *;

	[[nodiscard]]
	auto windowText() const -> QString;

signals:
	void windowTextChanged();

private:
	static constexpr QRgb color1 = 0xfffbf5ef;
	static constexpr QRgb color2 = 0xfff2d3ab;
	static constexpr QRgb color3 = 0xffc69fa5;
	static constexpr QRgb color4 = 0xff8b6d9c;
	static constexpr QRgb color5 = 0xff494d7e;
	static constexpr QRgb color6 = 0xff272744;

	[[nodiscard]]
	static auto toString(const QColor &color) -> QString;
};

QML_DECLARE_TYPEINFO(AppTheme, QML_HAS_ATTACHED_PROPERTIES)
