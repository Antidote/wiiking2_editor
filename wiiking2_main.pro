TEMPLATE = subdirs
CONFIG += ordered

wiiking2.depends += libzelda \
                    wiiking2_editor
SUBDIRS = libzelda \
          wiiking2_editor
