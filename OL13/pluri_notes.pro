HEADERS += \
    interface.h \
    Creation_Note.h \
    include.h \
    notes.h \
    QInclude.h \
    manager.h \
    undoredo.h \
    relations.h \
    aff_notes.h \
    qnote.h \
    qrelations.h \
    supp_note.h \
    quirelation.h \
    qmanagerelation.h \
    deletednote.h

QT += widgets
QT += xml
QT += multimedia
QT += core
QT += multimediawidgets

SOURCES += \
    interface.cpp \
    main.cpp \
    Creation_Note.cpp \
    notes.cpp \
    manager.cpp \
    undoredo.cpp \
    relations.cpp \
    aff_notes.cpp \
    qnote.cpp \
    qrelations.cpp \
    supp_note.cpp \
    quirelation.cpp \
    qmanagerelation.cpp \
    deletednote.cpp

FORMS += \
    quirelation.ui \
    qmanagerelation.ui \
    deletednote.ui
