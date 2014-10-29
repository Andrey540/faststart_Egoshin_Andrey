REM запуск программы для шифрования с нормальным входным файлом
crypt.exe crypt "test1.txt" "result1.txt" 212
IF ERRORLEVEL 1 GOTO err
REM запуск программы для расшифровки с нормальным входным файлом
crypt.exe decrypt "result1.txt" "result2.txt" 212
IF ERRORLEVEL 1 GOTO err
FC /B "test1.txt" "result2.txt"
IF ERRORLEVEL 1 GOTO err

REM запуск программы для шифрования с большим ключом
crypt.exe crypt "test3.txt" "result3.txt" 343
IF NOT ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
