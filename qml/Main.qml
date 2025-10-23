import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
	id: root
	title: "caw"
	visible: true
	width: 1280
	height: 720

	menuBar: MenuBar {
		Menu {
			title: "&File"
			Action {
				text: "&New..."
			}
			Action {
				text: "&Open..."
			}
			Action {
				text: "&Save"
				icon.name: ":/mdi/save-content.svg"
			}
			Action {
				text: "Save &As..."
			}
			Action {
				text: "&Export..."
			}
			MenuSeparator {
			}
			Action {
				text: "&Quit"
			}
		}
		Menu {
			title: "&Settings"
		}
		Menu {
			title: "&Debug"
		}
	}

	Label {
		text: "caw"
	}
}