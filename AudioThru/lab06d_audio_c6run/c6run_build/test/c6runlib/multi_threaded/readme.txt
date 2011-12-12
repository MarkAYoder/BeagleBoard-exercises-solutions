Description: 
  Call functions on the DSP from multiple threads on the GPP
Tests: 
  C6Run framework's ability to handle calls from multiple threads
Expected Result: 
  Program starts multiple threads, each thread makes a call to the DSP, 
  threads terminate execution and program shuts down normally.