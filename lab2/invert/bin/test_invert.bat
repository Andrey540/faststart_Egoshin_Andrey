REM ������ ��������� ��� ����������
invert.exe
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ���������� ����������, �� ���������� ������ �����
invert.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������� � �������� ������ �� ����������
invert.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ������
invert.exe "matrix1.txt" > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result1.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ������
invert.exe "matrix2.txt" > output.txt
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ���������� ������
invert.exe "matrix3.txt" > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result3.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
