#!/bin/sh

install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets flowed.app/Contents/MacOS/flowed
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore flowed.app/Contents/MacOS/flowed
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui flowed.app/Contents/MacOS/flowed

install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets flowed.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore flowed.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui flowed.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore

install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets flowed.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore flowed.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui flowed.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets flowed.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore flowed.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
install_name_tool -change /Users/Shared/Qt/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui flowed.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
