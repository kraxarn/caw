set(MDI_DIR "${mdi_SOURCE_DIR}/svg")

qt_add_resources(${PROJECT_NAME} "logos"
	PREFIX "/logos"
	BASE "res"
	FILES
	"res/caw.svg"
)

qt_add_resources(${PROJECT_NAME} "mdi"
	PREFIX "/mdi"
	BASE "${MDI_DIR}"
	FILES
	"${MDI_DIR}/bug.svg"
	"${MDI_DIR}/chevron-double-down.svg"
	"${MDI_DIR}/chevron-down.svg"
	"${MDI_DIR}/chevron-up.svg"
	"${MDI_DIR}/cog.svg"
	"${MDI_DIR}/content-duplicate.svg"
	"${MDI_DIR}/content-save.svg"
	"${MDI_DIR}/delete.svg"
	"${MDI_DIR}/export.svg"
	"${MDI_DIR}/file-plus.svg"
	"${MDI_DIR}/folder-open.svg"
	"${MDI_DIR}/link-off.svg"
	"${MDI_DIR}/link.svg"
	"${MDI_DIR}/minus.svg"
	"${MDI_DIR}/play.svg"
	"${MDI_DIR}/plus.svg"
	"${MDI_DIR}/record.svg"
	"${MDI_DIR}/repeat.svg"
	"${MDI_DIR}/sawtooth-wave.svg"
	"${MDI_DIR}/sine-wave.svg"
	"${MDI_DIR}/square-wave.svg"
	"${MDI_DIR}/step-forward.svg"
	"${MDI_DIR}/triangle-wave.svg"
)