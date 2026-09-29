@echo off
cd /d "%~dp0"
.\claat-windows-amd64.exe export .\_article\01_intro\01_intro.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\02_semiconductor\02_semiconductor.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\03_LED\03_LED.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\04_ultrasound\04_ultrasound.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\05_car_assembly\05_car_assembly.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\06_car_circuit\06_car_circuit.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\07_car_programming\07_car_programming.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\91_LED_quiz\91_LED_quiz.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\92_ultrasound_quiz\92_ultrasound_quiz.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\93_buzzer_quiz\93_buzzer_quiz.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\94_bluetooth_control\94_bluetooth_control.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\95_smartcar\95_smartcar.md
if errorlevel 1 exit /b 1
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0scripts\localize-assets.ps1"
exit /b %errorlevel%
