import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Imagine
import QtQuick.Layouts

import AppTheme

ApplicationWindow {
	id: root
	title: `${AppName} ${AppVersion} (Qt ${QtVersion})`
	visible: true
	width: 1280
	height: 720

	palette {
		windowText: AppTheme.windowText
	}

	Imagine.path: ":/themes/dark"

	menuBar: AppMenuBar {
	}

	Label {
		text: "caw"
	}
}