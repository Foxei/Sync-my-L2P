# Configure basic application and c++ version infromation
TEMPLATE = app
QT +=  core gui network xml
CONFIG += c++14
DESTDIR = bin

# Define application name
TARGET = Sync-my-L2P

# Define version and all following subversions to enriche the
# meta information provided to the os.
VERSION = 2.4.2
VERSIONS = $$split(VERSION, ".")
DEFINES += MAJOR_VERSION=$$member(VERSIONS, 0)
DEFINES += MINOR_VERSION=$$member(VERSIONS, 1)
DEFINES += REVISION=$$member(VERSIONS, 2)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Include all source and header files from this application
include(src/sync-my-l2p/Sync-my-L2p.pri)

# Include all source and header files from qslog as thirdparty lib
include(src/qslog/QsLog.pri)

# Include all gui files
FORMS += \
    res/gui/autoclosedialog.ui \
    res/gui/browser.ui \
    res/gui/dateidownloader.ui \
    res/gui/info.ui \
    res/gui/logger.ui \
    res/gui/logindialog.ui \
    res/gui/message.ui \
    res/gui/mymainwindow.ui \
    res/gui/options.ui

# Include all translation files
TRANSLATIONS = \
    res/lang/sync-my-l2p_de.ts \
    res/lang/sync-my-l2p_en.ts \
    res/lang/sync-my-l2p_lb.ts \
    res/lang/sync-my-l2p_sq.ts

# Include all resources files
RESOURCES += \
    res/icons/icons.qrc \
    res/lang/translation.qrc

# Include rc file
RC_FILE = res/icon.rc

# Include other files to be displayed in qt creator
OTHER_FILES += \
    res/Sync-my-L2P.icns \
    README.md \
    COPYING.LESSER \
    res/magnifier.ico \
    LICENSE \
    .gitignore

