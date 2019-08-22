
Debian
====================
This directory contains files used to package cbnd/cbn-qt
for Debian-based Linux systems. If you compile cbnd/cbn-qt yourself, there are some useful files here.

## cbn: URI support ##


cbn-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install cbn-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your cbnqt binary to `/usr/bin`
and the `../../share/pixmaps/cbn128.png` to `/usr/share/pixmaps`

cbn-qt.protocol (KDE)

