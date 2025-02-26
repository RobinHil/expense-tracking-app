QT       += core gui sql
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountdialog.cpp \
    chartsdialog.cpp \
    budgetdialog.cpp \
    deleteitemdialog.cpp \
    editpassworddialog.cpp \
    expense.cpp \
    category.cpp \
    expensedialog.cpp \
    expensetracking.cpp \
    hash.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    query.cpp \
    registerdialog.cpp \
    reminder.cpp \
    showcategorydialog.cpp \
    user.cpp \
    userdb.cpp

HEADERS += \
    accountdialog.h \
    chartsdialog.h \
    budgetdialog.h \
    deleteitemdialog.h \
    editpassworddialog.h \
    expense.h \
    category.h \
    expensedialog.h \
    hash.h \
    logindialog.h \
    mainwindow.h \
    expensetracking.h \
    query.h \
    registerdialog.h \
    reminder.h \
    showcategorydialog.h \
    user.h \
    userdb.h

FORMS += \
    accountdialog.ui \
    chartsdialog.ui \
    budgetdialog.ui \
    deleteitemdialog.ui \
    editpassworddialog.ui \
    expensedialog.ui \
    logindialog.ui \
    mainwindow.ui \
    registerdialog.ui \
    showcategorydialog.ui

TRANSLATIONS += \
    expense_tracking_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

# Adds compilation with libsodium library
unix: LIBS += -lsodium

win32|win64 {
    LIBS += -L$$PWD/resources/libsodium/lib/ -lsodium
    INCLUDEPATH += $$PWD/resources/libsodium/include
    DEPENDPATH += $$PWD/resources/libsodium/include
}

macx {
    INCLUDEPATH += /usr/local/opt/libsodium/include
    LIBS += -L/usr/local/opt/libsodium/lib -lsodium
}
