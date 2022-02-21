#!/bin/sh
set -eou pipefail
echo ./clean.sh && make richard && ./richard ${@:-}
