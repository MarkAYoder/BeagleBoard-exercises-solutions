Description: 
  Call a remote functions that will sit waiting while user/test harness is 
  supposed to supply a termination signal of some sort (e.g. Ctrl-C)
Tests: 
  Signal handling and abort mechanism of the C6Run framework while in the 
  middle of a remote function call.
Expected Result: 
  Program shutdowns correctly and DSP resources can be used again without reboot.