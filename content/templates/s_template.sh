for((i=1;;i++)); do
    echo $i
    ./gen $i > int
    diff -w <(./@ < int 2> /dev/null) <(./brute < int 2> /dev/null) || break
done
