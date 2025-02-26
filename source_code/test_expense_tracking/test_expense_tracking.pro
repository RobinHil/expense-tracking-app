QT = core gui sql
QT += testlib

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Ajout de l'option de compilation -lsodium
LIBS += -lsodium

DEPENDPATH += ../saeS3
INCLUDEPATH += $$PWD/../saeS3

SOURCES += \
        categorytest.cpp \
        dbsetup.cpp \
        expensetest.cpp \
        hashtest.cpp \
        main.cpp \
        remindertest.cpp \
        ../saeS3/expense.cpp \
        ../saeS3/category.cpp \
        ../saeS3/expensetracking.cpp \
        ../saeS3/hash.cpp \
        ../saeS3/reminder.cpp \
        ../saeS3/user.cpp \
        ../saeS3/userdb.cpp \
        ../saeS3/query.cpp \
        userdbtest.cpp \
        usertest.cpp

HEADERS += \
        categorytest.h \
        dbsetup.h \
        expensetest.h \
        hashtest.h \
        remindertest.h \
        ../saeS3/expense.h \
        ../saeS3/category.h \
        ../saeS3/hash.h \
        ../saeS3/expensetracking.h \
        ../saeS3/reminder.h \
        ../saeS3/user.h \
        ../saeS3/userdb.h \
        ../saeS3/query.h \
        userdbtest.h \
        usertest.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
