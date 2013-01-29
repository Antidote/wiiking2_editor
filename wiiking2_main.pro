TEMPLATE = subdirs
CONFIG += ordered

wiiking2.depends += libwiisave \
                    libzelda \
                    wiiking2_editor
SUBDIRS = libwiisave \
          libzelda \
          wiiking2_editor
