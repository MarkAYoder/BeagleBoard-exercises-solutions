Description:
  Compile and call a highly optimized C code function that makes use of 
  numerous C6x intrinsics and C6000 C-langauge specifics (like #pragma's).
Tests:
  Front-end ability to handle C code that contains optimizations for the DSP.
  In particular, tests the translation unit generation which is done by GCC.
Expected Result:
  The input C file can be properly analyzed and stubs can be properly
  generated for both the DSP and the GPP sides.