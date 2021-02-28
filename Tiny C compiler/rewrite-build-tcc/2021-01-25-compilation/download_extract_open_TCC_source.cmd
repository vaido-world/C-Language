@ECHO OFF
TITLE Compile Tiny C with itself AND run WinSocket example

SET "RandomNumber=%RANDOM%"
MKDIR "%RandomNumber%Directory"
CD "%RandomNumber%Directory"


ECHO Downloading "Old Precompiled Tiny C Compiler" in .zip archive format
curl -L "http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win64-bin.zip" -O

ECHO Extracting "Old Precompiled Tiny C Compiler" .zip Archive
tar xf "tcc-0.9.27-win64-bin.zip"

ECHO Downloading "Latest Tiny C Compiler Source Code"
curl "https://repo.or.cz/tinycc.git/snapshot/HEAD.tar.gz" -O

ECHO Extracting "Latest Tiny C Compiler Source Code" .tar.gz Archive
tar xf "HEAD.tar.gz"

CD "tinycc-HEAD-*/win32"

curl "https://github.com/vaido-world/C-Language-Tutorial/raw/master/Tiny%20C%20compiler/rewrite-build-tcc/2021-01-25-compilation/2draftconfig.h.cmd" -O

"C:\Windows\explorer.exe" "."
