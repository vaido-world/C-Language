# Reason to use Header files
https://stackoverflow.com/questions/11334371/cant-we-include-c-file/11334387#11334387

Always compile every .c source file separately! (as seen in **compile.cmd**)

GNU Make is a replacement for this compilation script in a large project.  
GNU Make manages what to build according to modified time, probably has caches and so on.  
Less processing/building every time - therefore more efficient.  
However We need a replacement for GNU Make since it is hard to read and understand.  
In the old days before Make we used bash scripts for building, turns out that having standard building system is less wasteful due to previous reasons.   
