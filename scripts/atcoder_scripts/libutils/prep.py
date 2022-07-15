#!/usr/local/bin/python
import argparse
from pathlib import Path
import yaml
import toml

def put_config(dirname):
    config_path = Path(__file__).parent / "config.yml"
    with open(config_path, 'rb') as _f:
        code = _f.read()
    with open(Path(dirname) / './config.yml', 'wb') as _f:
        _f.write(code)

def put_template(lang, dirname):
    config_path = Path(__file__).parent / "prepare.config.toml"
    config = dict(**toml.load(config_path))
    templates = config["templates"]
    if lang == "cpp":
        fname="main.cpp"
        path = templates[fname]
    elif lang == "python":
        fname="main.py"
        path = templates[fname]
    with open(path, 'rb') as _f:
        code = _f.read()
    extension=None
    if(lang=="cpp"): extension='cpp'
    if(lang=="python"): extension='py'
    with open(Path(dirname) / (Path(dirname).stem + f".{extension}"), 'wb') as _f:
        _f.write(code)

def prep(lang, dirname):
    Path(dirname).mkdir()
    (Path(dirname)/"tests").mkdir()
    put_template(lang, dirname)
    put_config(dirname)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-l", "--lang", default="cpp")
    args = parser.parse_args()
    put_config()
