QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Global.cpp \
    add_kala.cpp \
    add_to_cart.cpp \
    admin.cpp \
    article.cpp \
    cart.cpp \
    client.cpp \
    cloths.cpp \
    create_account.cpp \
    customer.cpp \
    edituser.cpp \
    factor.cpp \
    forget_password.cpp \
    game.cpp \
    load1.cpp \
    load2.cpp \
    load3.cpp \
    login.cpp \
    main.cpp \
    mythered.cpp \
    sporting_goods.cpp \
    test.cpp \
    transaction.cpp \
    transaction_customer.cpp \
    widget_kala.cpp \
    widget_show_kala_customer.cpp \
    widget_transactions.cpp \
    widget_user.cpp

HEADERS += \
    Global.h \
    Person.h \
    add_kala.h \
    add_to_cart.h \
    admin.h \
    article.h \
    cart.h \
    client.h \
    cloths.h \
    create_account.h \
    customer.h \
    edituser.h \
    factor.h \
    forget_password.h \
    game.h \
    load1.h \
    load2.h \
    load3.h \
    login.h \
    mythered.h \
    sporting_goods.h \
    test.h \
    transaction.h \
    transaction_customer.h \
    widget_kala.h \
    widget_show_kala_customer.h \
    widget_transactions.h \
    widget_user.h

FORMS += \
    add_kala.ui \
    add_to_cart.ui \
    admin.ui \
    cart.ui \
    client.ui \
    create_account.ui \
    customer.ui \
    edituser.ui \
    factor.ui \
    forget_password.ui \
    game.ui \
    load1.ui \
    load2.ui \
    load3.ui \
    login.ui \
    test.ui \
    transaction.ui \
    transaction_customer.ui \
    widget_kala.ui \
    widget_show_kala_customer.ui \
    widget_transactions.ui \
    widget_user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
    win32:RC_ICONS += instaler.ico

DISTFILES +=
