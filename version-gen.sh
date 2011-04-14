#!/bin/sh

GVF=$1
shift
DEF_VER=v0.0

LF='
'

# First see if there is a version file (included in release tarballs),
# then try git-describe, then default.
if test -f version
then
	VN=$(cat version) || VN="$DEF_VER"
elif git rev-parse --git-dir > /dev/null &&
	VN=$(git describe --match "v[0-9]*" --abbrev=4 HEAD 2>/dev/null) &&
	case "$VN" in
	*$LF*) (exit 1) ;;
	v[0-9]*)
		git update-index -q --refresh
		test -z "$(git diff-index --name-only HEAD --)" ||
		VN="$VN-dirty" ;;
	esac
then
	VN=$(echo "$VN" | sed -e 's/-/./g');
else
	VN="$DEF_VER"
fi

VN=$(expr "$VN" : v*'\(.*\)')

if test -r $GVF
then
	VC=$(sed -e 's/^#define KANOMI_VERSION //' <$GVF | sed -e 's/"//g')
else
	VC=unset
fi
test "$VN" = "$VC" || {
	echo >&2 "KANOMI_VERSION = $VN"
	echo "#define KANOMI_VERSION \"$VN\"" >$GVF
}


