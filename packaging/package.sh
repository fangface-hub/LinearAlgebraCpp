#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

if [ "$#" -ne 1 ] || { [ "$1" != deb ] && [ "$1" != rpm ]; }; then
  echo "Usage: sh packaging/package.sh {deb|rpm}" >&2
  exit 1
fi

if [ -n "${PACKAGE_VERSION:-}" ]; then
  version=$PACKAGE_VERSION
elif [ -f VERSION ]; then
  version=$(tr -d '[:space:]' < VERSION)
else
  echo "Error: VERSION file not found" >&2
  exit 1
fi
if ! printf '%s\n' "$version" | grep -Eq '^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)$'; then
  echo "Error: package version must be X.Y.Z (got '$version')" >&2
  exit 1
fi

if [ "$1" = deb ]; then
  tool=dpkg-deb
else
  tool=rpmbuild
fi
if ! command -v "$tool" >/dev/null 2>&1; then
  echo "Error: $tool is required to build the $1 package" >&2
  exit 1
fi

mkdir -p dist
dist=$(cd dist && pwd)
work=$(mktemp -d "${TMPDIR:-/tmp}/linearalgebracpp-package.XXXXXXXX")
trap 'rm -rf -- "$work"' EXIT HUP INT TERM

if [ "$1" = deb ]; then
  root=$work/deb
  mkdir -p "$root/DEBIAN" "$root/usr/local/include" \
    "$root/usr/share/doc/linearalgebracpp-dev"
  install -m 644 Include/Matrix.h Include/RowVector.h Include/ColVector.h \
    "$root/usr/local/include/"
  install -m 644 LICENSE "$root/usr/share/doc/linearalgebracpp-dev/copyright"
  cat > "$root/DEBIAN/control" <<EOF
Package: linearalgebracpp-dev
Version: $version
Section: libdevel
Priority: optional
Architecture: all
Maintainer: LinearAlgebraCpp maintainers <noreply@github.com>
Homepage: https://github.com/fangface-hub/LinearAlgebraCpp
Description: Header-only C++ linear algebra library
 A readable C++11 template library for matrices and vectors.
EOF
  dpkg-deb --build --root-owner-group "$root" \
    "$dist/linearalgebracpp-dev_${version}_all.deb"
else
  topdir=$work/rpmbuild
  mkdir -p "$topdir/BUILD" "$topdir/BUILDROOT" "$topdir/RPMS" \
    "$topdir/SOURCES" "$topdir/SPECS" "$topdir/SRPMS"
  tar -czf "$topdir/SOURCES/linearalgebracpp-${version}.tar.gz" \
    --transform "s,^,linearalgebracpp-${version}/," \
    Include/Matrix.h Include/RowVector.h Include/ColVector.h LICENSE
  rpmbuild -bb packaging/linearalgebracpp.spec \
    --define "_topdir $topdir" --define "package_version $version" \
    --define "_binary_payload w9.gzdio"
  install -m 644 "$topdir/RPMS/noarch/linearalgebracpp-devel-${version}-1.noarch.rpm" \
    "$dist/"
fi
