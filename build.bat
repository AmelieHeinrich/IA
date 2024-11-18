::
:: THIS BUILD SCRIPT IS PROVIDED BY AMELIE HEINRICH -- IF YOU HAVE ANY QUESTIONS, REFER TO THE FOLLOWING EMAIL ADDRESS: aheinrich@gaming.tech
:: CE SCRIPT DE BUILD A ETE ECRIT PAR AMELIE HEINRICH -- SI VOUS AVEZ DES QUESTIONS, ENVOYEZ LES MOI A CETTE ADRESSE EMAIL: aheinrich@gaming.tech
::
@echo off

:: If the Visual Studio command line isn't initialized, call vcvarsall x64 to do so. Gives access to commands like cl, link, lib, devenv, MSBuild etc.
WHERE cl
IF %ERRORLEVEL% NEQ 0 (
    call vcvarsall x64
)

:: Set the root directory. Used to get the absolute path of files
set rootDir=%cd%

:::::::: BEGIN SETTINGS

:: Set the output executable
set outputExe=IA.exe

:: Set source files
set source=%rootDir%/src/*.cc

:: Set include directories, modify to your needs
set includeDirs=/I%rootDir%/ext/include /I%rootDir%/include

:: Set library directories, if you need to link anything more, add the path to the libraries here
set libDirs=/LIBPATH:%rootDir%/ext/lib

:: Set link libraries. Modify to your needs
set links=user32.lib kernel32.lib

:: Set flags for the compiler, modify to your needs as well
set buildFlags=/EHsc /std:c++17 /Zi /w /MP /FC /nologo

:: Debug enabled?
set debug=false

:::::::: END SETTINGS
if %debug%==true (
    set debugFlags=/DEBUG:FULL
) else (
    set debugFlags=/DEBUG:NONE
)

:: Creates the build directory
if not exist run_tree (
    mkdir run_tree
)

pushd run_tree
cl %includeDirs% %buildFlags% %source% %debugFlags% -Fe%outputExe% /link /incremental %libDirs% %links%
popd
