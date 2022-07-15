#!/bin/bash
chmod +x --recursive /workspaces/atc-env/scripts/atcoder_scripts
apt-get install -y gdb
pip3 install -r .devcontainer/requirements.txt
bash /workspaces/atc-env/scripts/p

# precompile bits/stdc++.h
pch_dir=~/.cache/cxxpch
header_file=bits/stdc++.h
header_dir=`dirname "$header_file"`
mkdir -p $pch_dir/bits

[ ! -z "$pch_dir" ] ;  mkdir -p "$pch_dir"  
[ ! -z "$header_dir" ] ; mkdir -p "$header_dir" 
 
echo "#include <$header_file>" > "$header_file" \
  && g++ -x c++-header "$header_file" -o "$pch_dir/$header_file" \
  && rm "$header_file"

git clone git://github.com/gccxml/gccxml.git
cd gccxml
mkdir gccxml-build
cd gccxml-build
cmake ../gccxml
make
make install
cd ..
rm -rf gccxml

npm install -g typescript@3.8 ts-node @types/node
