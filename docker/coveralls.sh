#!/bin/bash -ex

CWD="$(cd -P -- "$(dirname -- $0)" && pwd -P)"

source "$CWD/build.sh"

if [ "${UPLOAD_COVERAGE}" == "yes" ]; then

    cpp-coveralls --verbose \
		  --encodings utf-8 latin-1 \
		  -E ".*/googletest.*" -E ".*/CMake.*"

elif [ -z "${UPLOAD_COVERAGE}" ]; then

    cpp-coveralls --verbose \
		  --encodings utf-8 latin-1 \
		  -E ".*/googletest.*" -E ".*/CMake.*" \
		  --dryrun

else

    echo "\$UPLOAD_COVERAGE must be 'yes' or ''"
    exit 1

fi
