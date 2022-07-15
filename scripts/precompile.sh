#!/bin/bash
set -aux
 
pch_dir=~/.cache/cxxpch
header_file=bits/stdc++.h
header_dir=`dirname "$header_file"`
mkdir -p $pch_dir/bits

echo $pch_dir
echo $header_dir
[ ! -z "$pch_dir" ] ;  mkdir -p "$pch_dir"  
[ ! -z "$header_dir" ] ; mkdir -p "$header_dir" 
 
echo "#include <$header_file>" > "$header_file" \
  && g++ -x c++-header "$header_file" -o "$pch_dir/$header_file" \
  && rm "$header_file"
