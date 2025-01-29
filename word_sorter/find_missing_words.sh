readarray -t a < format_list.txt

for word in "${a[@]}"
do
    if !( grep "$word" new_list.txt -q ); then
        echo "$word"
    fi
done
