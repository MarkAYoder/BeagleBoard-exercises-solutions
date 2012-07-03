Description: 
  Call collection of functions with coverage of scalar typedef arguments (from stdint.h).
Tests: 
  Frontend tools ability to handle typedef argument types and generate correct stubs
  and the framework tools ability to pass these typedefed arguments to remote procedures.
Expected Result: 
  Functions with scalar args of typedefed types can be compiled through C6RunLib framework
  and called successfully.
                 