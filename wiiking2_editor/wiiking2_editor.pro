#-------------------------------------------------
#
# Project created by QtCreator 2012-01-15T01:33:43
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:QMAKE_LFLAGS += -static

CONFIG(debug, debug|release){
    DEFINES += DEBUG INTERNAL
    unix:LIBS  += -L../libzelda -lzelda-d
    win32:LIBS += -L../libzelda -lzelda-d
}
CONFIG(release, release|debug){
    DEFINES -= DEBUG
    DEFINES += INTERNAL
    unix:LIBS  += -L../libzelda -lzelda
    win32:LIBS += -L../libzelda -lzelda
}

QMAKE_CXXFLAGS = -O0 -O1 -O2 -O3 -Os -std=c++11

TEMPLATE = app subdirs
unix:TARGET =../wiiking2_editor.x86_64
INCLUDEPATH += ./include \
           ../libzelda/include
unix:LIBS  += -lz
win32:LIBS += -lzlib

SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/newgamedialog.cpp \
    src/aboutdialog.cpp \
    src/fileinfodialog.cpp \
    src/skywardswordfile.cpp \
    src/wiikeys.cpp \
    src/preferencesdialog.cpp \
    src/checksum.cpp \
    src/common.cpp \
    src/qhexedit2/xbytearray.cpp \
    src/qhexedit2/qhexedit_p.cpp \
    src/qhexedit2/qhexedit.cpp \
    src/qhexedit2/commands.cpp \
    src/newfiledialog.cpp \
    src/gameinfowidget.cpp \
    src/settingsmanager.cpp \
    src/playtimewidget.cpp \
    src/importexportquestdialog.cpp \
    src/triforcewidget.cpp

HEADERS  += \
    include/mainwindow.h \
    include/igamefile.h \
    include/newgamedialog.h \
    include/aboutdialog.h \
    include/fileinfodialog.h \
    include/skywardswordfile.h \
    include/wiikeys.h \
    include/preferencesdialog.h \
    include/checksum.h \
    include/common.h \
    include/qhexedit2/xbytearray.h \
    include/qhexedit2/qhexedit_p.h \
    include/qhexedit2/qhexedit.h \
    include/qhexedit2/commands.h \
    include/newfiledialog.h \
    include/gameinfowidget.h \
    include/settingsmanager.h \
    include/playtimewidget.h \
    include/importexportquestdialog.h \
    include/triforcewidget.h

FORMS    += \
    forms/mainwindow.ui \
    forms/newgamedialog.ui \
    forms/aboutdialog.ui \
    forms/fileinfodialog.ui \
    forms/preferencesdialog.ui \
    forms/newfiledialog.ui \
    forms/gameinfowidget.ui \
    forms/playtimewidget.ui \
    forms/importexportquestdialog.ui

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    resources/mainicon.rc \
    resources/styleWin32.css \
    resources/styleUnix.css \
    resources/clockdisplay.css

TRANSLATIONS += \
    resources/languages/ja.ts

win32{
    RC_FILE = resources/mainicon.rc
}
