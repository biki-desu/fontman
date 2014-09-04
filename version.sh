#!/usr/bin/env bash

########################################################################
## Name:          version.sh
## Purpose:       Versioning
## Author:        lachs0r
## Modified by:   biki-desu
## Created:       2014/09/01
## Copyright:     (c) lachs0r
## Original file: https://github.com/lachs0r/SMPlayer2/commit/f8b87f4bc61e92c07c43f46bf1191e252125f938
## Licence:       GPLv2
########################################################################

if [ -e snapshot_version ] ; then
	VER="$(cat snapshot_version)"
else

git rev-list HEAD | sort > config.git-hash
LOCALVER=`wc -l config.git-hash | awk '{print $1}'`
if [ $LOCALVER -gt 1 ] ; then
	VER=`git rev-list origin/master | sort | join config.git-hash - | wc -l | awk '{print $1}'`
	if [ $VER != $LOCALVER ] ; then
		VER="$VER+$(($LOCALVER-$VER))"
	fi
	if git status | grep -q "modified:" ; then
		VER="${VER}M"
	fi
	VER=" r$VER $(git rev-list HEAD -n 1 | cut -c 1-7)"
fi
rm -f config.git-hash

fi

echo "$VER"
