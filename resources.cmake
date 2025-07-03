set(ICONS_BASE "${fontawesome_SOURCE_DIR}/svgs")
set(MDI_DIR "${mdi_SOURCE_DIR}/svg")

qt_add_resources(${PROJECT_NAME} "logos"
	PREFIX "/logos"
	BASE "res"
	FILES
	"res/caw.svg"
)

qt_add_resources(${PROJECT_NAME} "icons"
	PREFIX "/icons"
	BASE "${ICONS_BASE}"
	FILES
	"${ICONS_BASE}/solid/angles-down.svg"
	"${ICONS_BASE}/solid/bug.svg"
	"${ICONS_BASE}/solid/chevron-down.svg"
	"${ICONS_BASE}/solid/chevron-up.svg"
	"${ICONS_BASE}/solid/circle.svg"
	"${ICONS_BASE}/solid/clone.svg"
	"${ICONS_BASE}/solid/compact-disc.svg"
	"${ICONS_BASE}/solid/file-circle-plus.svg"
	"${ICONS_BASE}/solid/floppy-disk.svg"
	"${ICONS_BASE}/solid/folder-open.svg"
	"${ICONS_BASE}/solid/forward-step.svg"
	"${ICONS_BASE}/solid/gear.svg"
	"${ICONS_BASE}/solid/link-slash.svg"
	"${ICONS_BASE}/solid/link.svg"
	"${ICONS_BASE}/solid/minus.svg"
	"${ICONS_BASE}/solid/play.svg"
	"${ICONS_BASE}/solid/plus.svg"
	"${ICONS_BASE}/solid/repeat.svg"
	"${ICONS_BASE}/solid/rotate-right.svg"
	"${ICONS_BASE}/solid/xmark.svg"
)

qt_add_resources(${PROJECT_NAME} "mdi"
	PREFIX "/mdi"
	BASE "${MDI_DIR}"
	FILES
	"${MDI_DIR}/sine-wave.svg"
	"${MDI_DIR}/square-wave.svg"
	"${MDI_DIR}/sawtooth-wave.svg"
	"${MDI_DIR}/triangle-wave.svg"
)