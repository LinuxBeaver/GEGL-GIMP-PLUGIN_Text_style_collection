#!/bin/bash

# GETTEXT STATIC LINKING HEADER - Added for GIMP 3.2+ compatibility
# This finds gettext-windows two levels up and sets up static linking

# Find the master folder (two levels up from current plugin)
PLUGIN_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FILTERS_DIR="$(dirname "$PLUGIN_DIR")"
MASTER_DIR="$(dirname "$FILTERS_DIR")"

echo "========================================="
echo "Setting up static gettext for: $(basename $PLUGIN_DIR)"
echo "Plugin folder: $PLUGIN_DIR"
echo "Filters folder: $FILTERS_DIR"
echo "Master folder: $MASTER_DIR"
echo "========================================="

# Look for gettext-windows in master folder
if [ -d "$MASTER_DIR/gettext-windows" ]; then
    export GETTEXT_DIR="$MASTER_DIR/gettext-windows"
    echo "✅ Found gettext-windows at: $GETTEXT_DIR"
else
    echo "❌ ERROR: Cannot find gettext-windows/"
    echo "   Looked in: $MASTER_DIR/gettext-windows"
    echo ""
    echo "Please make sure gettext-windows is in the master folder:"
    echo "  $MASTER_DIR"
    exit 1
fi

# Set compiler flags for static linking
export CC="win-clang -fuse-ld=lld -target x86_64-w64-windows-gnu"
export CXX="win-clang++ -fuse-ld=lld -target x86_64-w64-windows-gnu"
export CFLAGS="-D__MINGW32__ -D__MINGW64__ -I$GETTEXT_DIR/include"
export LDFLAGS="-L$GETTEXT_DIR/lib -Wl,-Bstatic -lintl -liconv -Wl,-Bdynamic -static-libgcc"

echo "✅ Static gettext environment ready"
echo "========================================="
echo ""

mkdir WindowsBinaries

TOP=$(pwd)  

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'skeletontext.dll') $TOP/WindowsBinaries

cd ..

cd threshold_alpha_2 && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'thresholdalpha2.dll') $TOP/WindowsBinaries


