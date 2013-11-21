#!/bin/sh

#  fix_dylib.sh
#  chordrina
#
#  Created by Jianfeng Hu on 11/20/13.
#
cd ${TARGET_BUILD_DIR}
install_name_tool -change /usr/local/lib/libfluidsynth.1.dylib @executable_path/libfluidsynth.1.dylib chordrinaDebug.app/Contents/MacOS/chordrinaDebug
