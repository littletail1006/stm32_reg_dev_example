rem @echo off
echo ==============================================
echo          Keil Project Cleanup Tool
echo ==============================================
echo.

:: 设置要删除的文件扩展名
set EXTENSIONS=*.obj *.lst *.o *.d *.axf *.hex *.bin *.map *.lnp *.build_log.htm *.dep *.crf *.htm *.sct *.bak

:: 设置要搜索的子目录
set DIRS=Objects Listings

echo 正在清理当前目录及子目录中的临时文件...
echo.

:: 删除当前目录下的目标文件
for %%e in (%EXTENSIONS%) do (
    if exist "%%e" (
        echo 删除文件: %%e
        del /f /q "%%e"
    )
)

:: 删除指定子目录中的文件
for %%d in (%DIRS%) do (
    if exist "%%d\" (
        echo 进入目录: %%d
        for %%e in (%EXTENSIONS%) do (
            if exist "%%d\%%e" (
                echo 删除文件: %%d\%%e
                del /f /q "%%d\%%e"
            )
        )
        echo.
    )
)

:: 搜索并删除所有子目录中的临时文件
echo 正在搜索所有子目录中的临时文件...
for /r %%f in (%EXTENSIONS%) do (
    if exist "%%f" (
        echo 删除文件: %%f
        del /f /q "%%f"
    )
)

echo.
echo ==============================================
echo          清理完成!
echo ==============================================
rem pause