:: set directories to match your installation
set examples_drawables_dir="C:\oc_projekt\cobjapi\examples\drawables"
set src_c_dir="C:\oc_projekt\cobjapi\src_c"
set src_cobol_dir="C:\oc_projekt\cobjapi\src_cobol"

:: test if directories exist
if not exist "%examples_drawables_dir%\" (
   echo Please set examples_drawables_dir correct, currently set to %examples_drawables_dir%
   goto :eof
)
if not exist "%src_c_dir%\" (
   echo Please set src_c_dir correct, currently set to %src_c_dir%
   goto :eof
)
if not exist "%src_cobol_dir%\" (
   echo Please set src_cobol_dir correct, currently set to %src_cobol_dir%
   goto :eof
)

:: delete old files (ignoring errors)
del "%examples_drawables_dir%\*.obj"    2>NUL
del "%examples_drawables_dir%\*.lib"    2>NUL
del "%examples_drawables_dir%\*.exp"    2>NUL
del "%examples_drawables_dir%\*.exe"    2>NUL

:: set env. variables
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat"

:: set compiler parameters
SET COBCOBJ=cobjapi.obj fileselect.obj imageio.obj japilib.obj
SET COBCLIB=-lWS2_32.Lib

:: change directory
cd %examples_drawables_dir%

:: compile the C programs
cobc -c -v %src_c_dir%\fileselect.c
cobc -c -v %src_c_dir%\imageio.c
cobc -c -v %src_c_dir%\japilib.c

:: compile the cobjapi interface
cobc -c -free -v %src_cobol_dir%\cobjapi.cob

:: compile the program
cobc -x -free -v -I%src_cobol_dir% drawables.cob %COBCOBJ% %COBCLIB%


:eof

pause
