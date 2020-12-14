Dim objShell, strPath1, strAttr1, strAttr2, strAttr3
Set objShell = CreateObject ("WScript.Shell")

strPath1 = """tcc"""
strAttr1 = " -run "
strAttr2 = """C:\Users\Juozas\Desktop\yourFirstWindowsProgram.c"""
'strAttr3 = " nogui"

objShell.Run strPath1 & strAttr1 & strAttr2 & strAttr3, 0, true
