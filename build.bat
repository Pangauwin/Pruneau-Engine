@ECHO OFF
SetLocal EnableDelayedExpansion

SET buildDir=./bin/
SET exeName=PruneauEngine

CD src

FOR /R %%f in (*.c *.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

CD ../ext

FOR /R %%f in (*.c *.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

CD ..

SET libFilenames=opengl32.lib comdlg32.lib

CD lib

FOR /R %%f in (*.lib) do (
    SET libFilenames=!libFilenames! %%f
)

CD ..

SET compilerFlags=/Zi /EHsc /std:c++17

SET includeFlags=/I "./include" /I "./src"

SET defines=-D_DEBUG -DUNICODE -D_UNICODE

ECHO Building...

CALL "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

@ECHO ON

cl %compilerFlags% %includeFlags% /Fe:%buildDir%%exeName%.exe %cFilenames% /link %libFilenames%

@ECHO OFF

ECHO Cleaning...

FOR /R %%f in (*.obj) do (
    DEL %%f
)