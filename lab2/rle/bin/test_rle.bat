REM запуск программы для упаковки с нормальным входным файлом
rle.exe pack "test1.txt" "result1.txt"
IF ERRORLEVEL 1 GOTO err
REM запуск программы для распаковки с нормальным входным файлом
rle.exe unpack "result1.txt" "result2.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "test1.txt" "result2.txt"
IF ERRORLEVEL 1 GOTO err

REM запуск программы для упаковки с нормальным входным файлом
rle.exe pack "test3.txt" "result3.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "result3.txt" "check3.txt"
IF ERRORLEVEL 1 GOTO err

REM запуск программы для упаковки с нормальным входным файлом
rle.exe pack "test4.txt" "result4.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "result4.txt" "check4.txt"
IF ERRORLEVEL 1 GOTO err

REM запуск программы для упаковки с нормальным входным файлом
rle.exe pack "test5.txt" "result5.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "result5.txt" "check5.txt"
IF ERRORLEVEL 1 GOTO err

REM запуск программы для упаковки с нормальным входным файлом
rle.exe unpack "test6.txt" "result6.txt"
IF NOT ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
