import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

MenuBar {
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
			icon.name: ":/mdi/content-save.svg"
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