TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    src/restqtful.pro \
    example
example.depends = src

