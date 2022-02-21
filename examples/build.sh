#!/bin/sh
set -eou pipefail
./clean.sh && make richard && ./richard ${@:-}
