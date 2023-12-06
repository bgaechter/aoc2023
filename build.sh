#!/bin/bash

usage() {
	echo "Usage: $0 [-d <Day of AoC>] [-D]" 1>&2
	echo "-D: Enable Debug"
	exit 1
}

while getopts ":Dd:" o; do
	case "${o}" in
	D)
		DEBUG=true
		;;
	d)
		DAY=${OPTARG}
		;;
	*)
		usage
		;;
	esac
done
shift $((OPTIND - 1))

if [ -n "${DEBUG}" ]; then
	cmake --build "$(pwd)/build" --config Debug -j --target all --
else
	cmake --build "$(pwd)/build" --config Release -j --target all --
fi

if [ -n "${DEBUG}" ] && [ -n "${DAY}" ]; then
	lldb "$(pwd)/build/bin/aoc2023" "${DAY}"
	exit 0
fi

if [ -n "${DEBUG}" ]; then
	lldb "$(pwd)/build/bin/aoc2023" "${DAY}"
	exit 0
fi

if [ -n "${DAY}" ]; then
	"$(pwd)/build/bin/aoc2023" "${DAY}"
	exit 0
fi

"$(pwd)/build/bin/aoc2023" "$(date +%d)"
