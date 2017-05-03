#!/bin/bash

destination="./build"
commit="HEAD"
snapshot=true

while getopts "c:v:r" opt
do
  case $opt in
    c) commit="$OPTARG"
       ;;
    r) snapshot=false
       ;;
    v) version="$OPTARG"
       ;;
  esac
done

if [ -z "$version" ]; then
  # If the version arg is missing and the commit is the current HEAD, we can read the version
  # number from the VERSION file

  if [ "$commit" != "HEAD" ]; then
    printf "Expects version arg for commits other than HEAD\n"
    printf "Usage: $0 [-c <commit> -v <version>] [-s]\n"
    exit 1
  fi

  version=$(cat ./VERSION)
fi

if [ "$commit" = "HEAD" ]; then
  if [ ! -z "$(git status --porcelain)" ]; then
    printf "Warning: There are uncommitted changes. Building from HEAD.\n"
  fi
fi

if [ "$snapshot" = true ]; then
  suffix="-SNAPSHOT"
else
  suffix=""
fi

printf "Building archive... "

tmpArchiveName="tmp.tar.gz"
git archive --format=tar.gz -o "$destination/$tmpArchiveName" "$commit"

cd "$destination"

unpackedDir="hangman-$version$suffix"
archiveName="hangman_$version$suffix.orig.tar.gz"

mkdir -p "$unpackedDir"

tar -xkf "$tmpArchiveName" -C "$unpackedDir"
rm "$tmpArchiveName"

tar -czf  "$archiveName" "$unpackedDir"
rm -r "$unpackedDir"

cd ..
printf "Done\n"
