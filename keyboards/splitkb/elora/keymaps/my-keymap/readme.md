# Elora Keymap: My-Keymap

This keymap is designed for the Elora keyboard. Elora includes support for multiple layers, combos, and RGB lighting. 

The keymap is tailored for both Windows and macOS users, with specific layers for gaming.

# Hardware Support

Elora has OLED screen on both sides. A matrixs of 12 LEDs provide underglow, but these are not per key.

# Building diagrams:

https://github.com/caksoylar/keymap-drawer

parse requires manually naming the layer names

qmk c2json ~/Documents/git/qmk_firmware_elora/keyboards/splitkb/elora/keymaps/my-keymap/keymap.c | keymap parse --layer-names BASE M_BASE _G_BASE _NAV _M_NAV NUM _M_NUM _MERGE _M_MERGE _MEDIA _M_MEDIA -c 10 -q - > ~/Documents/git/qmk_firmware_elora/keyboards/splitkb/elora/keymaps/my-keymap/keymap.yaml

keymap draw ~/Documents/git/qmk_firmware_elora/keyboards/splitkb/elora/keymaps/my-keymap/keymap.yaml > ~/Documents/git/qmk_firmware_elora/keyboards/splitkb/elora/keymaps/my-keymap/keymap.svg


# Build firmware

qmk compile -kb <keyboard> -km <keymap>


# Layers Overview

~/Documents/git/qmk_firmware_elora/keyboards/splitkb/elora/keymaps/my-keymap/keymap.svg

# MAC

Uses GB British
@@@@


# Windows

# TODO

[ ] Review symbol keybindings and print off.
[ ] Create a better swapper
[ ] Modify basic MERGE
[ ] Modify basic MEDIA
[ ] mod morph function keys
[ ] 
