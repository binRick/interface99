#!/bin/sh
set -eou pipefail
echo ./clean.sh && cmake . && make richard && ./richard ${@:-}
