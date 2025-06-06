# https://github.com/Homebrew/homebrew-cask/blob/master/Casks/font/font-f/font-fontawesome.rb
set(FONTAWESOME_VERSION "6.7.2")
set(FONTAWESOME_HASH "22ff7898b429b997a45e1cf89bb869ed3abcc65333d90289181ba5363c8fd19b")

include(FetchContent)

FetchContent_Declare(
	fontawesome
	URL "https://github.com/FortAwesome/Font-Awesome/releases/download/${FONTAWESOME_VERSION}/fontawesome-free-${FONTAWESOME_VERSION}-desktop.zip"
	URL_HASH "SHA256=${FONTAWESOME_HASH}"
	DOWNLOAD_EXTRACT_TIMESTAMP true
)
message(STATUS "Downloading icons")
FetchContent_MakeAvailable(fontawesome)