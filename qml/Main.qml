import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Imagine
import QtQuick.Layouts

ApplicationWindow {
	id: root
	title: `${AppName} ${AppVersion} (Qt ${QtVersion})`
	visible: true
	width: 1280
	height: 720

	Imagine.path: ":/themes/dark"

	menuBar: AppMenuBar {
	}

	Label {
		text: "caw"
	}
}