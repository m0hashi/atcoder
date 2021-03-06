#!/usr/local/bin/python
import yaml
from distutils import file_util
import CppHeaderParser
import glob
import argparse
import json
from pathlib import Path

PREFIX = "lib/"
CPP_SNIPPETS_PATH = "/workspaces/atc-env/.vscode/cpplib.code-snippets"
# CPPLIB_PATH='/workspaces/atc-env/snippets/cpp/_src'
CPPLIB_PATH = "/workspaces/atc-env/snippets/cpp"
PYLIB_PATH = "/workspaces/atc-env/snippets/cpp"


class Module:
    """ファイル単位にその中に存在するクラス、関数を抜き出して保持する"""

    def __init__(self, filepath, key, contents):
        self.config_location = filepath
        self.__functions = []
        self.__classes = []
        self.__config = contents
        self.key = key
        self.set_properties(contents)
        self.read_module(contents)

    def set_properties(self, contents):
        self.__modulepath = contents["modulePath"]

    def read_module(self, config):
        if config.get("classes") is not None:
            self.__classes = self.read_classes(config["classes"])
        if config.get("functions") is not None:
            self.__functions = self.read_functions(config["functions"])

    def read_body(self, filepath, line_number):
        return_body = []
        with open(filepath) as f:
            src_lines = list(map(lambda s: s.rstrip(), f.readlines()))
        bra_counts = 0
        ket_counts = 0
        for line in src_lines[line_number - 1 :]:
            bra_counts += sum([1 if w == "{" else 0 for w in line])
            ket_counts += sum([1 if w == "}" else 0 for w in line])
            return_body.append(line)
            if bra_counts == ket_counts:
                break
        return return_body

    def read_classes(self, cls_cfg):
        targets = list(cls_cfg.keys())
        header = CppHeaderParser.CppHeader(self.module_path)
        classes = []
        for name, cls in header.classes.items():
            if name not in targets:
                continue
            if cls["parent"] is not None:
                continue
            body = []
            cls = header.classes[name]
            if "template" in cls.keys():
                body.append(cls["template"])
            body += self.read_body(self.module_path, cls["line_number"])
            classes.append(
                {
                    "type": "class",
                    "name": name,
                    "snippet_name": cls_cfg[name]["snippetName"],
                    "filename": self.module_path,
                    "body": body,
                }
            )
        return classes

    def read_functions(self, func_cfg):
        targets = list(func_cfg.keys())
        header = CppHeaderParser.CppHeader(self.module_path)
        functions = []
        for func in header.functions:
            function_name = func["name"]
            if function_name not in targets:
                continue
            body = []
            if "template" in func.keys():
                if func["template"]:
                    body.append(func["template"])
            body += self.read_body(self.module_path, func["line_number"])
            functions.append(
                {
                    "type": "function",
                    "name": func["name"],
                    "snippet_name": func_cfg[function_name]["snippetName"],
                    "filename": self.module_path,
                    "body": body,
                }
            )
        return functions

    @property
    def module_path(self):
        return Path(self.config_location).parent / self.__modulepath

    @property
    def classes(self):
        return self.__classes

    @property
    def module(self):
        return

    @property
    def functions(self):
        return self.__functions

    @property
    def classes(self):
        return self.__classes

    @property
    def functions(self):
        return self.__functions


class ModuleListManager:
    def __init__(self, filepath):
        self.filepath = filepath
        self.__modules = self.load_config(filepath)
        print(self.filepath)

    def load_config(self, filepath):
        contents = self.read_file(filepath)
        configs = self._parse_contents(filepath, contents)
        return configs

    def _parse_contents(self, filepath, contents):
        modules = []
        for _k, _c in contents.items():
            modules.append(Module(filepath, _k, _c))
        return modules

    def read_file(self, filepath):
        with open(filepath) as f:
            data = yaml.safe_load(f)
        return data

    def __getitem__(self, key):
        return self.__modules[key]


class CPPSnippetsWriter:
    def __init__(self, cpp_snippets_path, config_path_list):
        self.cpp_snipetts_path = cpp_snippets_path
        self.config_path_list = config_path_list

    def load_snippets(self, path_list):
        print(path_list)
        module_managers = []
        snippets = {"classes": [], "functions": []}
        for path in path_list:
            module_managers.append(ModuleListManager(path))
        for managers in module_managers:
            for module in managers:
                snippets["classes"] += module.classes
                snippets["functions"] += module.functions
        return snippets

    def write_snippets(self, snippets):
        snippets_json = {}
        for key in ['functions', 'classes']:
            for snippet in snippets[key]:
                print(snippet['body'])
                data = {
                    "scope": "cpp",
                    "prefix": snippet["snippet_name"],
                    "body": snippet["body"],
                    "description": f"{snippet['filename']}",
                }
                snippets_json[snippet["name"]] = data
            with open(self.cpp_snipetts_path, "w", encoding='utf-8') as f:
                json.dump(snippets_json, f, indent=4, ensure_ascii=False)

    def update_snippets(self):
        snippets = self.load_snippets(self.config_path_list)
        self.write_snippets(snippets)
        
def update_cpp_snippet():
    configpath_list = glob.glob(CPPLIB_PATH + "/**/*.yml", recursive=True)
    writer = CPPSnippetsWriter(CPP_SNIPPETS_PATH, configpath_list)
    writer.update_snippets()
    

def main(lang: str):
    if lang == "cpp":
        update_cpp_snippet()
    elif lang == "py":
        pass


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("lang", default="cpp")
    args = parser.parse_args()
    main(args.lang)
