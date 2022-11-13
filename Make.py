import os, sys

sourcef: str = '.\Source'
outputf: str = '.\Output'
objectf: str = f'{outputf}\Object'

class Project:
  folder: str = 'E:\Projects\KPLC'
  name: str = 'kplc'
  binary: str = f'{outputf}\{name}.exe'
  flags: str = '-std=c++20 -O3 -g -Wall -Wextra -Werror'

  def __init__(self):
    if not os.path.exists(outputf):
      os.mkdir(outputf)
    if not os.path.exists(objectf):
      os.mkdir(objectf)
    self.folders: list[str] = []
    self.files: list[tuple(str, str)] = []
    for (path, folders, files) in os.walk(sourcef):
      for folder in folders:
        folder = f'{objectf}\{folder}'
        if not os.path.exists(folder):
          os.mkdir(folder)
        folder = f'{path}\{folder}'
        self.folders += folder
        self.flags += f' -I{folder}'
      for file in files:
        if file[len(file) - 3: len(file)] == 'hpp':
          continue
        source: str = f'{path}\{file}'
        object: str = source.replace(sourcef, objectf, 1).removesuffix('cpp') + 'obj'
        self.files.append(tuple((source, object)))

  def build(self) -> None:
    objects: str = ''
    build_failed: bool = False
    for (source, object) in self.files:
      objects += f'{object} '
      if os.path.exists(object):
        print(f'"{object}" already exists.')
        continue
      print(f'clang++ -c {source} -o {object} {self.flags}')
      if os.system(f'clang++ -c {source} -o {object} {self.flags}'):
        build_failed = True
    if build_failed:
      print('Build failed.')
      exit()
    os.system(f'clang++ {objects} -o {self.binary} {self.flags}')

  def run(self, args: str) -> None:
    if not os.path.exists(self.binary):
      self.build()
    print(f'{self.binary} {args}')
    os.system(f'{self.binary} {args}')

  def clean(self) -> None:
    for (_, object) in self.files:
      if not os.path.exists(object):
        continue
      os.remove(object)

  def format(self) -> None:
    ffiles: str = ''
    for (path, _, files) in os.walk(sourcef):
      for file in files:
          ffiles += f'{path}\{file} '
    print(f'clang-format -i {ffiles}')
    os.system(f'clang-format -i {ffiles}')

  def diff() -> None:
    os.system('git status')
    os.system('git diff --state')

project = Project()
args: list[str] = sys.argv
args_len = len(args)
if args_len == 1:
  print('Option was not provided.')
  exit()
arg: str = args[1]
if arg == 'build':
  project.build()
elif arg == 'run':
  project.run('E:\Projects\KPLC\Tests\A.kpl')
elif arg == 'clean':
  project.clean()
elif arg == 'format':
  project.format()
elif arg == 'diff':
  project.diff()
else:
  print(f'"{arg}" is not a valid argument.')
