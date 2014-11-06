#! /bin/bash
##datetime	
numProcesses=$(ps aux | wc -l)

numUsers=$(users | wc -w)

totalRamSize=$( free -m | awk '/^Mem:/ {print $2}')
usedRamSize=$( free -m | awk '/^Mem:/ {print $3}')

usedMemoryPercent=$(echo "$usedRamSize $totalRamSize" |  awk '{printf "%.0f", $1/$2*100}' )

echo $(date +%x) $(date +%H) $numProcesses $numUsers $usedMemoryPercent% >> CT320HW3.dat