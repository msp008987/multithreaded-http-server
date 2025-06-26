#!/bin/bash
mkdir -p results

CONCURRENCY_LIST=(10 50 100 200)
REQUESTS=1000
URL="http://localhost:8080/"
CSV_FILE="results/performance.csv"
echo "Concurrency,Requests,RequestsPerSec,AvgTimePerReq(ms)" > $CSV_FILE

for C in "${CONCURRENCY_LIST[@]}"; do
    echo "Testing with concurrency: $C"
    OUTPUT=$(ab -n $REQUESTS -c $C $URL)
    REQ_PER_SEC=$(echo "$OUTPUT" | grep "Requests per second" | awk '{print $4}')
    AVG_TIME=$(echo "$OUTPUT" | grep "Time per request:" | head -n 1 | awk '{print $4}')
    echo "$C,$REQUESTS,$REQ_PER_SEC,$AVG_TIME" >> $CSV_FILE
done
