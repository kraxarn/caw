#pragma once

#include <QString>

class Format final
{
public:
	template<typename T>
	static auto hex(T value) -> QString
	{
		return QStringLiteral("%1")
			.arg(value, 2, 16, QChar::fromLatin1('0'))
			.toUpper();
	}

private:
	Format() = default;
};
