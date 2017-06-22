# README
Project for experiment minimum

## Install ROOT
1. Download v5.34/23 (Platform: Windows Visual Studio 11)  
https://root.cern.ch/content/release-53423  

2. Execute or extract downloaded file

## Setting Project in Visual Studio
After create empty win32 console application

1. Project -> Property
2. Add `$(ROOTSYS)\include` in [Configuration Properties - > C/C++ -> Additional Include Directories]
3. Add `$(ROOTSYS)\lib` in [Configuration Properties - > Linker -> Additional Library Directories]
4. Add required .lib files in [Configuration Properties - > Linker -> Input -> Additional Dependencies]

*`$(ROOTSYS)`: ROOT installed location (e.g. `C:\root_v5.34.23` by default of .exe version)*