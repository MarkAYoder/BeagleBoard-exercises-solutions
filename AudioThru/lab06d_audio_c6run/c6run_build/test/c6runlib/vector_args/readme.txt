Description:
  Call collection of functions with coverage of vector pass-by-pointer 
  arguments (pointers to all built-in C integer and real types). Uses
  C6RUN_MEM_malloc to allocate buffers for passing to the DSP.
Tests:
  Frontend tools ability to handle vector/buffer argument types and framework
  tools ability to pass buffer arguments to remote procedures. Also tests 
  caching operations on ARM and DSP sides.
Expected Result:
  Functions with buffer/vector args can be compiled through C6RunLib framework
  and called successfully.