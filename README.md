# COMRunner
A simple COM server which provides a component to run shellcode. Also includes a Windows JScript file to
load the COM server and create the object with registration-free activation. This PoC COM server provides an object
with a method that takes in base64 encoded shellcode and a method to run the shellcode.

For a more exhaustive background, see the blog post here: https://adapt-and-attack.com/2020/05/12/building-a-com-server-for-initial-execution/

## Contents
COM Client (JScript) to activate the object and run shellcode
- `script.js`

COM Class definition and C++ implementation:
- `COMRunner\object.cpp`
- `COMRunner\object.h`

IDL Object Definition:
- `COMRunner\TestClass.idl`

Generated files from [midl.exe](https://docs.microsoft.com/en-us/windows/win32/midl/using-the-midl-compiler-2) compilation:
- `COMRunner\TestClass.h`
- `COMRunner\TestClass.tlb`
- `COMRunner\TestClass_i.c`
- `COMRunner\TestClass_p.c`
- `COMRunner\dlldata.c`

Resource Embedding:
- `COMRunner\resource.rc` specifying resources to embed
- `COMRunner\resource.res` generated file from `rc COMRunner\resource.rc`, file is pulled in to embed TLB at compile time

Other:
- `COMRunner\dllmain.cpp` has typical dllmain functions and `DllGetClassObject` implementation
- `COMRunner\Helpers.h` includes some helper functions
- `COMRunner\Source.def` defines exported functions

## Changing the Object
As described later in the blog post, which is probably the best way to understand if this is new to you,
the COM object's structure is identified in the `TestClass.idl` file. If you want to add another method
or take an additional input, you will want to follow these general steps. These may not be the only way, so feel
free to stray away as well.

1. Update the `TestClass.idl` with your desired changes
2. Regenerate files with `midl.exe TestClass.idl`
3. The new TLB needs to be embedded. Run `rc resource.rc` to generated a new `resource.res`
4. Update `object.h` class to ensure it implements your new interface defined in `TestClass.idl`
5. Update `object.cpp` to change/add/remove your object's method's code

## Thanks
- Much thanks to [@subTee](https://twitter.com/subTee) for the research this was built on: https://www.youtube.com/watch?v=BIJ2L_rM9Gc
- [Inside COM](https://www.amazon.com/Inside-Microsoft-Programming-Dale-Rogerson/dp/1572313498) by Dale Rogerson
- For ClassFactory code: https://www.codeguru.com/cpp/com-tech/activex/tutorials/article.php/c5567/Step-by-Step-COM-Tutorial.htm
