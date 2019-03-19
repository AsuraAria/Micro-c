SET PATH=D:\Programs\MDK\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\iCLS\;C:\Program Files\Intel\Intel(R) Management Engine Components\iCLS\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Windows Live\Shared;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\;%SYSTEMROOT%\System32\OpenSSH\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files\WorldPainter;C:\Android;C:\Users\ElexXVII\AppData\Local\Microsoft\WindowsApps;C:\Users\ElexXVII\AppData\Local\atom\bin;C:\Users\ElexXVII\AppData\Local\GitHubDesktop\bin
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Open1786
SET CPU_CLOCK=0x00B71B00
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_lpc17xx._ia"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_lpc17xx.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_clkpwr.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_gpio.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_pinsel.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_timer.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_exti.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_nvic.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_ssp.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_i2c.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\ili_lcd_general.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lcd_api.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\english_16x8.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\affichagelcd.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\touch_panel.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\display.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\memory.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\output\musicien.__i"
"D:\Programs\MDK\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\Project.lnp"
"D:\Programs\MDK\ARM\ARMCC\Bin\fromelf.exe" ".\Output\Project.axf" --i32combined --output ".\Output\Project.hex"
