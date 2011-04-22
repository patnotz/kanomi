#!/bin/sh

VS=$1
shift
HEADER_PATH=$1
shift
VH="$HEADER_PATH/Kanomi_autoversion.hpp"

VERSION=$($VS)

if test -r $VH 
then
	PREVIOUS_VERSION=$(grep KANOMI_VERSION $VH | sed -e 's/^#define KANOMI_VERSION //' | sed -e 's/"//g')
else
	PREVIOUS_VERSION=unset
fi

if test "$VERSION" != "$PREVIOUS_VERSION"
then
	echo "#ifndef KANOMI_AUTOVERSION_HPP_" > $VH
	echo "#define KANOMI_AUTOVERSION_HPP_" >> $VH
	echo "" >> $VH
	echo "#define KANOMI_VERSION \"$VERSION\"" >> $VH
	echo "#endif // KANOMI_AUTOVERSION_HPP_" >> $VH
fi
