:: set directories to match your installation
set examples_video_dir="C:\oc_projekt\cobjapi\examples\video"
set src_c_dir="C:\oc_projekt\cobjapi\src_c"
set src_cobol_dir="C:\oc_projekt\cobjapi\src_cobol"

:: test if directories exist
if not exist "%examples_video_dir%\" (
   echo Please set examples_video_dir correct, currently set to %examples_video_dir%
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
del "%examples_video_dir%\*.obj"    2>NUL
del "%examples_video_dir%\*.lib"    2>NUL
del "%examples_video_dir%\*.exp"    2>NUL
del "%examples_video_dir%\*.exe"    2>NUL

:: set env. variables
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

:: set compiler parameters
SET COBCOBJ=cobjapi.obj fileselect.obj imageio.obj japilib.obj
SET COBCLIB=-lWS2_32.Lib

:: change directory
cd %examples_video_dir%

:: compile the C programs
cobc -c -v %src_c_dir%\fileselect.c
cobc -c -v %src_c_dir%\imageio.c
cobc -c -v %src_c_dir%\japilib.c

:: compile the cobjapi interface
cobc -c -free -v %src_cobol_dir%\cobjapi.cob

:: compile the program
cobc -x -free -v -I%src_cobol_dir% video.cob %COBCOBJ% %COBCLIB%


:eof

pause
