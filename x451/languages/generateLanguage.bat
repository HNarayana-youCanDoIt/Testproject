rem set path="%path%;D:\ProgramFiles\Qt\5.10.0\msvc2015_64\bin"

cd %PWD%

echo %cd%
del *.ts 
del *.qm
echo "generating language files"
lupdate ..\TML_X451_HMI.pro
lupdate ..\TML_X104VAVE_HMI.pro
lupdate ..\TML_X445_HMI.pro

echo "Updating language files"
LangTranslate Language.csv en_IN.ts en_US.ts

echo "generating qm"
lrelease ..\TML_X451_HMI.pro
lrelease ..\TML_X104VAVE_HMI.pro
lrelease ..\TML_X445_HMI.pro
