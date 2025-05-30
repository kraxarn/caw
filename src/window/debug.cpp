#include "window/debug.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QTabWidget>
#include <QScrollArea>

Debug::Debug(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);

	auto *tabs = new QTabWidget(this);
	layout->addWidget(tabs);

	tabs->addTab(iconsTab(), QStringLiteral("Icons"));
}

auto Debug::iconsTab() -> QWidget *
{
	auto *widget = new QWidget(this);
	auto *layout = new QGridLayout(widget);

	for (auto i = 0; i < static_cast<int>(QIcon::ThemeIcon::NThemeIcons); i++)
	{
		constexpr auto iconSize = 32;

		const auto themeIcon = static_cast<QIcon::ThemeIcon>(i);
		if (!QIcon::hasThemeIcon(themeIcon))
		{
			continue;
		}

		const auto iconPixmap = QIcon::fromTheme(themeIcon).pixmap(iconSize, iconSize);
		auto *icon = new QLabel(widget);
		icon->setPixmap(iconPixmap);
		layout->addWidget(icon, i, 0);

		auto *label = new QLabel(iconName(themeIcon), widget);
		layout->addWidget(label, i, 1);
	}

	auto *scrollArea = new QScrollArea(this);
	scrollArea->setWidget(widget);

	return scrollArea;
}

auto Debug::iconName(QIcon::ThemeIcon themeIcon) -> QString
{
	// For some reason ThemeIcon isn't declared with Q_ENUM, so we can't use metadata

	switch (themeIcon)
	{
		case QIcon::ThemeIcon::AddressBookNew: return QStringLiteral("AddressBookNew");
		case QIcon::ThemeIcon::ApplicationExit: return QStringLiteral("ApplicationExit");
		case QIcon::ThemeIcon::AppointmentNew: return QStringLiteral("AppointmentNew");
		case QIcon::ThemeIcon::CallStart: return QStringLiteral("CallStart");
		case QIcon::ThemeIcon::CallStop: return QStringLiteral("CallStop");
		case QIcon::ThemeIcon::ContactNew: return QStringLiteral("ContactNew");
		case QIcon::ThemeIcon::DocumentNew: return QStringLiteral("DocumentNew");
		case QIcon::ThemeIcon::DocumentOpen: return QStringLiteral("DocumentOpen");
		case QIcon::ThemeIcon::DocumentOpenRecent: return QStringLiteral("DocumentOpenRecent");
		case QIcon::ThemeIcon::DocumentPageSetup: return QStringLiteral("DocumentPageSetup");
		case QIcon::ThemeIcon::DocumentPrint: return QStringLiteral("DocumentPrint");
		case QIcon::ThemeIcon::DocumentPrintPreview: return QStringLiteral("DocumentPrintPreview");
		case QIcon::ThemeIcon::DocumentProperties: return QStringLiteral("DocumentProperties");
		case QIcon::ThemeIcon::DocumentRevert: return QStringLiteral("DocumentRevert");
		case QIcon::ThemeIcon::DocumentSave: return QStringLiteral("DocumentSave");
		case QIcon::ThemeIcon::DocumentSaveAs: return QStringLiteral("DocumentSaveAs");
		case QIcon::ThemeIcon::DocumentSend: return QStringLiteral("DocumentSend");
		case QIcon::ThemeIcon::EditClear: return QStringLiteral("EditClear");
		case QIcon::ThemeIcon::EditCopy: return QStringLiteral("EditCopy");
		case QIcon::ThemeIcon::EditCut: return QStringLiteral("EditCut");
		case QIcon::ThemeIcon::EditDelete: return QStringLiteral("EditDelete");
		case QIcon::ThemeIcon::EditFind: return QStringLiteral("EditFind");
		case QIcon::ThemeIcon::EditPaste: return QStringLiteral("EditPaste");
		case QIcon::ThemeIcon::EditRedo: return QStringLiteral("EditRedo");
		case QIcon::ThemeIcon::EditSelectAll: return QStringLiteral("EditSelectAll");
		case QIcon::ThemeIcon::EditUndo: return QStringLiteral("EditUndo");
		case QIcon::ThemeIcon::FolderNew: return QStringLiteral("FolderNew");
		case QIcon::ThemeIcon::FormatIndentLess: return QStringLiteral("FormatIndentLess");
		case QIcon::ThemeIcon::FormatIndentMore: return QStringLiteral("FormatIndentMore");
		case QIcon::ThemeIcon::FormatJustifyCenter: return QStringLiteral("FormatJustifyCenter");
		case QIcon::ThemeIcon::FormatJustifyFill: return QStringLiteral("FormatJustifyFill");
		case QIcon::ThemeIcon::FormatJustifyLeft: return QStringLiteral("FormatJustifyLeft");
		case QIcon::ThemeIcon::FormatJustifyRight: return QStringLiteral("FormatJustifyRight");
		case QIcon::ThemeIcon::FormatTextDirectionLtr: return QStringLiteral("FormatTextDirectionLtr");
		case QIcon::ThemeIcon::FormatTextDirectionRtl: return QStringLiteral("FormatTextDirectionRtl");
		case QIcon::ThemeIcon::FormatTextBold: return QStringLiteral("FormatTextBold");
		case QIcon::ThemeIcon::FormatTextItalic: return QStringLiteral("FormatTextItalic");
		case QIcon::ThemeIcon::FormatTextUnderline: return QStringLiteral("FormatTextUnderline");
		case QIcon::ThemeIcon::FormatTextStrikethrough: return QStringLiteral("FormatTextStrikethrough");
		case QIcon::ThemeIcon::GoDown: return QStringLiteral("GoDown");
		case QIcon::ThemeIcon::GoHome: return QStringLiteral("GoHome");
		case QIcon::ThemeIcon::GoNext: return QStringLiteral("GoNext");
		case QIcon::ThemeIcon::GoPrevious: return QStringLiteral("GoPrevious");
		case QIcon::ThemeIcon::GoUp: return QStringLiteral("GoUp");
		case QIcon::ThemeIcon::HelpAbout: return QStringLiteral("HelpAbout");
		case QIcon::ThemeIcon::HelpFaq: return QStringLiteral("HelpFaq");
		case QIcon::ThemeIcon::InsertImage: return QStringLiteral("InsertImage");
		case QIcon::ThemeIcon::InsertLink: return QStringLiteral("InsertLink");
		case QIcon::ThemeIcon::InsertText: return QStringLiteral("InsertText");
		case QIcon::ThemeIcon::ListAdd: return QStringLiteral("ListAdd");
		case QIcon::ThemeIcon::ListRemove: return QStringLiteral("ListRemove");
		case QIcon::ThemeIcon::MailForward: return QStringLiteral("MailForward");
		case QIcon::ThemeIcon::MailMarkImportant: return QStringLiteral("MailMarkImportant");
		case QIcon::ThemeIcon::MailMarkRead: return QStringLiteral("MailMarkRead");
		case QIcon::ThemeIcon::MailMarkUnread: return QStringLiteral("MailMarkUnread");
		case QIcon::ThemeIcon::MailMessageNew: return QStringLiteral("MailMessageNew");
		case QIcon::ThemeIcon::MailReplyAll: return QStringLiteral("MailReplyAll");
		case QIcon::ThemeIcon::MailReplySender: return QStringLiteral("MailReplySender");
		case QIcon::ThemeIcon::MailSend: return QStringLiteral("MailSend");
		case QIcon::ThemeIcon::MediaEject: return QStringLiteral("MediaEject");
		case QIcon::ThemeIcon::MediaPlaybackPause: return QStringLiteral("MediaPlaybackPause");
		case QIcon::ThemeIcon::MediaPlaybackStart: return QStringLiteral("MediaPlaybackStart");
		case QIcon::ThemeIcon::MediaPlaybackStop: return QStringLiteral("MediaPlaybackStop");
		case QIcon::ThemeIcon::MediaRecord: return QStringLiteral("MediaRecord");
		case QIcon::ThemeIcon::MediaSeekBackward: return QStringLiteral("MediaSeekBackward");
		case QIcon::ThemeIcon::MediaSeekForward: return QStringLiteral("MediaSeekForward");
		case QIcon::ThemeIcon::MediaSkipBackward: return QStringLiteral("MediaSkipBackward");
		case QIcon::ThemeIcon::MediaSkipForward: return QStringLiteral("MediaSkipForward");
		case QIcon::ThemeIcon::ObjectRotateLeft: return QStringLiteral("ObjectRotateLeft");
		case QIcon::ThemeIcon::ObjectRotateRight: return QStringLiteral("ObjectRotateRight");
		case QIcon::ThemeIcon::ProcessStop: return QStringLiteral("ProcessStop");
		case QIcon::ThemeIcon::SystemLockScreen: return QStringLiteral("SystemLockScreen");
		case QIcon::ThemeIcon::SystemLogOut: return QStringLiteral("SystemLogOut");
		case QIcon::ThemeIcon::SystemSearch: return QStringLiteral("SystemSearch");
		case QIcon::ThemeIcon::SystemReboot: return QStringLiteral("SystemReboot");
		case QIcon::ThemeIcon::SystemShutdown: return QStringLiteral("SystemShutdown");
		case QIcon::ThemeIcon::ToolsCheckSpelling: return QStringLiteral("ToolsCheckSpelling");
		case QIcon::ThemeIcon::ViewFullscreen: return QStringLiteral("ViewFullscreen");
		case QIcon::ThemeIcon::ViewRefresh: return QStringLiteral("ViewRefresh");
		case QIcon::ThemeIcon::ViewRestore: return QStringLiteral("ViewRestore");
		case QIcon::ThemeIcon::WindowClose: return QStringLiteral("WindowClose");
		case QIcon::ThemeIcon::WindowNew: return QStringLiteral("WindowNew");
		case QIcon::ThemeIcon::ZoomFitBest: return QStringLiteral("ZoomFitBest");
		case QIcon::ThemeIcon::ZoomIn: return QStringLiteral("ZoomIn");
		case QIcon::ThemeIcon::ZoomOut: return QStringLiteral("ZoomOut");
		case QIcon::ThemeIcon::AudioCard: return QStringLiteral("AudioCard");
		case QIcon::ThemeIcon::AudioInputMicrophone: return QStringLiteral("AudioInputMicrophone");
		case QIcon::ThemeIcon::Battery: return QStringLiteral("Battery");
		case QIcon::ThemeIcon::CameraPhoto: return QStringLiteral("CameraPhoto");
		case QIcon::ThemeIcon::CameraVideo: return QStringLiteral("CameraVideo");
		case QIcon::ThemeIcon::CameraWeb: return QStringLiteral("CameraWeb");
		case QIcon::ThemeIcon::Computer: return QStringLiteral("Computer");
		case QIcon::ThemeIcon::DriveHarddisk: return QStringLiteral("DriveHarddisk");
		case QIcon::ThemeIcon::DriveOptical: return QStringLiteral("DriveOptical");
		case QIcon::ThemeIcon::InputGaming: return QStringLiteral("InputGaming");
		case QIcon::ThemeIcon::InputKeyboard: return QStringLiteral("InputKeyboard");
		case QIcon::ThemeIcon::InputMouse: return QStringLiteral("InputMouse");
		case QIcon::ThemeIcon::InputTablet: return QStringLiteral("InputTablet");
		case QIcon::ThemeIcon::MediaFlash: return QStringLiteral("MediaFlash");
		case QIcon::ThemeIcon::MediaOptical: return QStringLiteral("MediaOptical");
		case QIcon::ThemeIcon::MediaTape: return QStringLiteral("MediaTape");
		case QIcon::ThemeIcon::MultimediaPlayer: return QStringLiteral("MultimediaPlayer");
		case QIcon::ThemeIcon::NetworkWired: return QStringLiteral("NetworkWired");
		case QIcon::ThemeIcon::NetworkWireless: return QStringLiteral("NetworkWireless");
		case QIcon::ThemeIcon::Phone: return QStringLiteral("Phone");
		case QIcon::ThemeIcon::Printer: return QStringLiteral("Printer");
		case QIcon::ThemeIcon::Scanner: return QStringLiteral("Scanner");
		case QIcon::ThemeIcon::VideoDisplay: return QStringLiteral("VideoDisplay");
		case QIcon::ThemeIcon::AppointmentMissed: return QStringLiteral("AppointmentMissed");
		case QIcon::ThemeIcon::AppointmentSoon: return QStringLiteral("AppointmentSoon");
		case QIcon::ThemeIcon::AudioVolumeHigh: return QStringLiteral("AudioVolumeHigh");
		case QIcon::ThemeIcon::AudioVolumeLow: return QStringLiteral("AudioVolumeLow");
		case QIcon::ThemeIcon::AudioVolumeMedium: return QStringLiteral("AudioVolumeMedium");
		case QIcon::ThemeIcon::AudioVolumeMuted: return QStringLiteral("AudioVolumeMuted");
		case QIcon::ThemeIcon::BatteryCaution: return QStringLiteral("BatteryCaution");
		case QIcon::ThemeIcon::BatteryLow: return QStringLiteral("BatteryLow");
		case QIcon::ThemeIcon::DialogError: return QStringLiteral("DialogError");
		case QIcon::ThemeIcon::DialogInformation: return QStringLiteral("DialogInformation");
		case QIcon::ThemeIcon::DialogPassword: return QStringLiteral("DialogPassword");
		case QIcon::ThemeIcon::DialogQuestion: return QStringLiteral("DialogQuestion");
		case QIcon::ThemeIcon::DialogWarning: return QStringLiteral("DialogWarning");
		case QIcon::ThemeIcon::FolderDragAccept: return QStringLiteral("FolderDragAccept");
		case QIcon::ThemeIcon::FolderOpen: return QStringLiteral("FolderOpen");
		case QIcon::ThemeIcon::FolderVisiting: return QStringLiteral("FolderVisiting");
		case QIcon::ThemeIcon::ImageLoading: return QStringLiteral("ImageLoading");
		case QIcon::ThemeIcon::ImageMissing: return QStringLiteral("ImageMissing");
		case QIcon::ThemeIcon::MailAttachment: return QStringLiteral("MailAttachment");
		case QIcon::ThemeIcon::MailUnread: return QStringLiteral("MailUnread");
		case QIcon::ThemeIcon::MailRead: return QStringLiteral("MailRead");
		case QIcon::ThemeIcon::MailReplied: return QStringLiteral("MailReplied");
		case QIcon::ThemeIcon::MediaPlaylistRepeat: return QStringLiteral("MediaPlaylistRepeat");
		case QIcon::ThemeIcon::MediaPlaylistShuffle: return QStringLiteral("MediaPlaylistShuffle");
		case QIcon::ThemeIcon::NetworkOffline: return QStringLiteral("NetworkOffline");
		case QIcon::ThemeIcon::PrinterPrinting: return QStringLiteral("PrinterPrinting");
		case QIcon::ThemeIcon::SecurityHigh: return QStringLiteral("SecurityHigh");
		case QIcon::ThemeIcon::SecurityLow: return QStringLiteral("SecurityLow");
		case QIcon::ThemeIcon::SoftwareUpdateAvailable: return QStringLiteral("SoftwareUpdateAvailable");
		case QIcon::ThemeIcon::SoftwareUpdateUrgent: return QStringLiteral("SoftwareUpdateUrgent");
		case QIcon::ThemeIcon::SyncError: return QStringLiteral("SyncError");
		case QIcon::ThemeIcon::SyncSynchronizing: return QStringLiteral("SyncSynchronizing");
		case QIcon::ThemeIcon::UserAvailable: return QStringLiteral("UserAvailable");
		case QIcon::ThemeIcon::UserOffline: return QStringLiteral("UserOffline");
		case QIcon::ThemeIcon::WeatherClear: return QStringLiteral("WeatherClear");
		case QIcon::ThemeIcon::WeatherClearNight: return QStringLiteral("WeatherClearNight");
		case QIcon::ThemeIcon::WeatherFewClouds: return QStringLiteral("WeatherFewClouds");
		case QIcon::ThemeIcon::WeatherFewCloudsNight: return QStringLiteral("WeatherFewCloudsNight");
		case QIcon::ThemeIcon::WeatherFog: return QStringLiteral("WeatherFog");
		case QIcon::ThemeIcon::WeatherShowers: return QStringLiteral("WeatherShowers");
		case QIcon::ThemeIcon::WeatherSnow: return QStringLiteral("WeatherSnow");
		case QIcon::ThemeIcon::WeatherStorm: return QStringLiteral("WeatherStorm");
		default: return QString::number(static_cast<int>(themeIcon));
	}
}
