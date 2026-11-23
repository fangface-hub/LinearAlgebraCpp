#!/bin/sh
set -eu

cd "$(dirname "$0")/.."
source_dir=$(pwd)
work=$(mktemp -d "${TMPDIR:-/tmp}/linearalgebracpp-package-test.XXXXXXXX")
trap 'rm -rf -- "$work"' EXIT HUP INT TERM

mkdir -p "$work/project"
cp Makefile LICENSE VERSION "$work/project/"
cp -R Include packaging "$work/project/"
cd "$work/project"
unset PACKAGE_VERSION
expected=$(tr -d '[:space:]' < VERSION)
make deb
[ "$(dpkg-deb -f "dist/linearalgebracpp-dev_${expected}_all.deb" Version)" = "$expected" ]
printf '2.3.4\n' > VERSION

make release-package
deb=dist/linearalgebracpp-dev_2.3.4_all.deb
rpm=dist/linearalgebracpp-devel-2.3.4-1.noarch.rpm
[ "$(dpkg-deb -f "$deb" Version)" = 2.3.4 ]
[ "$(rpm -qp --qf '%{VERSION}' "$rpm")" = 2.3.4 ]
[ "$(rpm -qp --qf '%{ARCH}' "$rpm")" = noarch ]
dpkg-deb -x "$deb" "$work/deb"
for header in Matrix.h RowVector.h ColVector.h; do
  cmp "$source_dir/Include/$header" "$work/deb/usr/local/include/$header"
  rpm -qlp "$rpm" | grep -Fx "/usr/local/include/$header" >/dev/null
done
cmp "$source_dir/LICENSE" \
  "$work/deb/usr/share/doc/linearalgebracpp-dev/copyright"
rpm -qlp "$rpm" | grep -E '/LICENSE$' >/dev/null

PACKAGE_VERSION=3.4.5 make deb
[ "$(dpkg-deb -f dist/linearalgebracpp-dev_3.4.5_all.deb Version)" = 3.4.5 ]
if PACKAGE_VERSION=invalid make deb; then
  echo "Error: invalid version was accepted" >&2
  exit 1
fi
