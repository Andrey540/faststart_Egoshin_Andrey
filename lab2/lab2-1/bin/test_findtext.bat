REM ������ ��������� ��� ����������
findtext.exe
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������
findtext.exe "pascalFile.txt"
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������� � �������� ������ �� ����������
findtext.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������� (� ��������� ���������)
findtext.exe "pascalFile.txt" BEGIN
IF ERRORLEVEL 1 GOTO err
FC /B output.txt BEGIN.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����������� (������� ������ �������� ��� � �����)
findtext.exe "pascalFile.txt" begin
IF NOT ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
