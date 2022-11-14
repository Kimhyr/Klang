switch (Args[0].ToLower()) {
case "run":
  if (!File.Exists(@".\Output\kplc.exe")) {
    Console.Write("Executable was not generated.");
    break;
  }
  ExecuteCommand(@".\Output\kplc.exe", "");
  break;
case "build":
  Build();
  break;
case "clean":
  Clean();
  break;
case "format":
  Format();
  break;
default:
  Console.Write($"The arg {Args[0]} is undefined.\n");
  break;
}

void Build() {
  var flags = "-std=c++20 -O3 -Wall -Wextra -Werror";
  foreach (var dir in Directory.GetDirectories(@".\Source", "*", SearchOption.AllDirectories)) {
    flags += $" -I{dir}";
    var objDir = dir.Replace(@".\Source", @".\Output\Objects");
    if (!Directory.Exists(objDir)) {
      Console.Write($"Creating the {objDir} because it  does not exist.\n");
      Directory.CreateDirectory(objDir);
    }
  }
  var srcs = Directory.GetFiles(@".\Source", "*.cpp", SearchOption.AllDirectories);
  var objs = new List<String>();
  var isExitFailed = false;
  foreach (var src in srcs) {
    var obj = src.Replace(".cpp", ".obj").Replace(@".\Source", @".\Output\Objects");
    objs.Add(obj);
    if (File.Exists(obj)) {
      Console.Write($"Skipping because the file '{obj}' already exists.\n");
      continue;
    }
    var cargs = $"-c {src} -o {obj} {flags}";
    Console.Write($"clang++ {cargs}\n");
    if (!isExitFailed) {
      isExitFailed = ExecuteCommand("clang++", cargs) > 0;
    }
  }
  if (isExitFailed) {
    Console.Write("The executable is unable to be generated because an error occurred during compilation.\n");
    return;
  }
  var args = "";
  foreach (var obj in objs) {
    args += $"{obj} ";
  }
  args += $@"-o .\Output\kplc.exe {flags}";
  Console.Write($"clang++ {args}\n");
  var exit = ExecuteCommand("clang++", args);
}

void Clean() {
  foreach (var file in Directory.GetFiles(@".\Output", "*", SearchOption.AllDirectories)) {
    Console.Write($"Deleting the file {file}...\n");
    File.Delete(file);
  }
}

void Format() {
  String args = "-i";
  foreach (var file in Directory.GetFiles(@".\Source", "*", SearchOption.AllDirectories)) {
    args += $" {file}";
  }
  Console.Write($"clang-format {args}\n");
  ExecuteCommand("clang-format", args);
}

Int32 ExecuteCommand(String executable, String args) {
  var process = new Process();
  process.StartInfo.FileName = executable;
  process.StartInfo.Arguments = args;
  process.StartInfo.UseShellExecute = false;
  process.StartInfo.RedirectStandardOutput = true;
  process.OutputDataReceived += (sender, outf) => Console.Write(outf.Data);
  process.Start();
  process.BeginOutputReadLine();
  process.WaitForExit();
  return process.ExitCode;
}
