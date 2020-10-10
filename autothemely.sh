#!/bin/bash

echo export DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS > lightscript.sh
echo export DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS > darkscript.sh
echo "gsettings set org.gnome.desktop.interface gtk-theme WhiteSur-light" >> lightscript.sh
echo "gsettings set org.gnome.desktop.interface icon-theme WhiteSur" >> lightscript.sh
echo "gsettings set org.gnome.shell.extensions.user-theme name WhiteSur-light" >> lightscript.sh
echo "gsettings set org.gnome.desktop.background picture-uri file:///home/hryan/Pictures/macOS-BS-Walls/macOS-BS3.jpg" >> lightscript.sh
echo "gsettings set org.gnome.desktop.interface gtk-theme WhiteSur-dark" >> darkscript.sh
echo "gsettings set org.gnome.desktop.interface icon-theme WhiteSur-dark" >> darkscript.sh
echo "gsettings set org.gnome.shell.extensions.user-theme name WhiteSur-dark" >> darkscript.sh
echo "gsettings set org.gnome.desktop.background picture-uri file:///home/hryan/Pictures/macOS-BS-Walls/macOS-BS2.jpg" >> darkscript.sh
chmod 755 lightscript.sh
chmod 755 darkscript.sh

currenttime=$(date +%H:%M)
if [[ "$currenttime" > "18:00" ]] || [[ "$currenttime" < "06:00" ]]; then
     ./darkscript.sh
else
     ./lightscript.sh
fi
