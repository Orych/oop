
set PROGRAM="%~1"

rem Regular 
%PROGRAM% 5 > %TEMP%\output01.txt
fc calcbits01.txt %TEMP%\output01.txt
if ERRORLEVEL 1 goto err

rem Regular with 0
%PROGRAM% 0 > %TEMP%\output01.txt
fc calcbits02.txt %TEMP%\output01.txt
if ERRORLEVEL 1 goto err

rem Regular with 255
%PROGRAM% 255 > %TEMP%\output01.txt
fc calcbits03.txt %TEMP%\output01.txt
if ERRORLEVEL 1 goto err

rem Regular without diaposon
%PROGRAM% 300 > %TEMP%\output01.txt
fc calcbits04.txt %TEMP%\output01.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed