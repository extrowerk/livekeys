
# Plugin build configuration,
# !!! Modify only if you know what you are doing

TEMPLATE = subdirs

# Optional build modules

SUBDIRS += \
    live \
    editor \
    editqml \
    fs \
    lcvcore \
    lcvimgproc \
    lcvfeatures2d \
    lcvphoto \
    lcvvideo

# --- Subdir configuration ---

lcvcore.subdir          = $$PWD/lcvcore
lcvimgproc.subdir       = $$PWD/lcvimgproc
lcvfeatures2d.subdir    = $$PWD/lcvfeatures2d
live.subdir             = $$PWD/live
editor.subdir           = $$PWD/editor
editqml.subdir          = $$PWD/editqml
fs.subdir               = $$PWD/fs
lcvphoto.subdir         = $$PWD/lcvphoto
lcvvideo.subdir         = $$PWD/lcvvideo

# --- Dependency configuration ---

live.depends          = editor
editqml.depends       = live
lcvcore.depends       = live
lcvfeatures2d.depends = lcvcore live
lcvimgproc.depends    = lcvcore live
lcvphoto.depends      = lcvcore live
lcvvideo.depends      = lcvcore live

!isEmpty(BUILD_ELEMENTS){
    SUBDIRS += editlv
    editlv.depends = live
    editlv.subdir = $$PWD/editlv

    SUBDIRS += editjson
    editjson.depends = live
    editjson.subdir = $$PWD/editjson

    SUBDIRS += language
    language.subdir = $$PWD/language

    SUBDIRS += test
    test.subdir = $$PWD/test
}
