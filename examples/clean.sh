#!/bin/bash
set -e
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
source .envrc
find . -name "*.unc-backup*" -type f | xargs -I % unlink %
reset

(
	uncrustify --replace \
		richard*.*


find . -name "*.unc-backup*" -type f | xargs -I % unlink %
  { rm .v*.dump||true; } 2>/dev/null
) 
