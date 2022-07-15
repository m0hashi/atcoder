from distutils.command.config import config
from modulefinder import LOAD_CONST
import yaml
import glob
from pathlib import Path

CPPLIB_PATH='/workspaces/atc-env/snippets/cpp/_src'
CPPLIB_PATH='/workspaces/atc-env/snippets/cpp'
configpath_list = glob.glob(CPPLIB_PATH+"/**/*.yml", recursive=True)
print(configpath_list)


class Module:
    def __init__(self, filepath, key, contents):
        self.config_location = filepath
        self.set_properties(contents)

    def set_properties(self, contents):
        print(contents)
        self.__modulepath = contents['modulePath']
        self.__classes = contents['classes']
    
    @property
    def module_path(self):
        return Path(self.config_location).parent / self.__modulepath

    @property
    def classes(self):
        return self.__classes

class ConfigFile:
    def __init__(self, filepath):
        self.filepath = filepath
        self.configs = self.load_config(filepath)
        
    def load_config(self, filepath):
        contents = self.read_file(filepath)
        configs = self._parse_contents(filepath, contents)
        return configs
    
    def _parse_contents(self,filepath, contents):
        configs = []
        for _k, _c in contents.items():
            configs.append(Module(filepath, _k, _c))
        return configs
        
    def read_file(self, filepath):
        with open(filepath) as f:
            data = yaml.safe_load(f)
        return data
    
    def __getitem__(self, key):
        return self.configs[key]


cf = ConfigFile(configpath_list[0])
print(cf[0].module_path)
print(cf[0].classes)
