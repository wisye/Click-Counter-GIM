Yes, i only use raw C on windows
Yes, i did not use any game engine
Yes, it's only 56kb
QR CODE only contains the source code from LastLifeOptimized.c

LastLife.c : Contains the original code
LastLife.exe : Executable of the original code without optimization so it's 254kb
LastLifeOptimized.c : Contains optimized version of the code so it can fit inside a QR code
LastLifeOptimized.obj : Object file of LastLife.c so i can optimize it even further using a manual linker and a packer for executables
LastLifeOptimized.exe : Executable of the code with optimization and it's 56kb
LastLife.png : Contains an optimized code in a QR CODE

To run it you will need a compiler and run:
1. gcc LastLifeOptimized.c -o LastLife -lgdi32
2. .\LastLife.exe

If you wanna make it 56kb:
1. Open developer command prompt for vs 2022
2. Navigate into your directory
3. Make an obj file using this command
   cl /Fe:LastLifeOptimized.exe /link /NODEFAULTLIB /ENTRY:main SUBSYSTEM:WINDOWS LastLifeOptimized.obj user32.lib gdi32.lib
4. Make an exe file using this command
   link /OUT:LastLife.exe LastLifeOptimized.obj user32.lib gdi32.lib
5. Install upx and open it in another command prompt
6. Run this command
   upx --best "LastLife.exe" -o "LastLifeOptimized.exe"