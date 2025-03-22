#!/bin/bash

set -e

APP_NAME="minipass"
ICON_NAME="minipass"
ICON_DIR="$HOME/.local/share/icons/hicolor"
DESKTOP_FILE="$HOME/.local/share/applications/$ICON_NAME.desktop"

mkdir -p "$ICON_DIR/16x16/apps"
mkdir -p "$ICON_DIR/24x24/apps"
mkdir -p "$ICON_DIR/32x32/apps"
mkdir -p "$ICON_DIR/48x48/apps"
mkdir -p "$ICON_DIR/64x64/apps"
mkdir -p "$ICON_DIR/72x72/apps"
mkdir -p "$ICON_DIR/96x96/apps"
mkdir -p "$ICON_DIR/128x128/apps"
mkdir -p "$ICON_DIR/256x256/apps"

cp "resources/icon/minipass-16x16.png" "$ICON_DIR/16x16/apps/$ICON_NAME.png"
cp "resources/icon/minipass-24x24.png" "$ICON_DIR/24x24/apps/$ICON_NAME.png"
cp "resources/icon/minipass-32x32.png" "$ICON_DIR/32x32/apps/$ICON_NAME.png"
cp "resources/icon/minipass-48x48.png" "$ICON_DIR/48x48/apps/$ICON_NAME.png"
cp "resources/icon/minipass-64x64.png" "$ICON_DIR/64x64/apps/$ICON_NAME.png"
cp "resources/icon/minipass-72x72.png" "$ICON_DIR/72x72/apps/$ICON_NAME.png"
cp "resources/icon/minipass-96x96.png" "$ICON_DIR/96x96/apps/$ICON_NAME.png"
cp "resources/icon/minipass-128x128.png" "$ICON_DIR/128x128/apps/$ICON_NAME.png"
cp "resources/icon/minipass-256x256.png" "$ICON_DIR/256x256/apps/$ICON_NAME.png"

cat > "$DESKTOP_FILE" <<EOF
[Desktop Entry]
Name=$APP_NAME
Exec=$HOME/Documents/minipass/minipass
Icon=$ICON_DIR/256x256/apps/$ICON_NAME.png
Type=Application
Categories=Utility;
StartupWMClass=minipass;
EOF

update-desktop-database $HOME/.local/share/applications || echo "Icon cache update failed, might not be needed."

echo "Installation complete! Try running 'minipass' from your application menu."
