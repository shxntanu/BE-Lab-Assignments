#!/bin/bash

echo "Enter subject (DAA/ML/BT): "
read SUBJECT

BASE_URL="https://raw.githubusercontent.com/shxntanu/BE-Lab-Assignments/main/"

case "$SUBJECT" in
"DAA" | "ML" | "BT")
    cd "$SUBJECT" || {
        echo "Directory does not exist!"
        exit 1
    }
    ;;
*)
    echo "Invalid subject name. Please choose from DAA, ML, or BT."
    exit 1
    ;;
esac

files=(*)
echo "Files in the $SUBJECT directory:"
for i in "${!files[@]}"; do
    echo "$((i + 1)). ${files[i]}"
done

echo "Enter the number of the file you want to download:"
read FILE_NUMBER

if ! [[ "$FILE_NUMBER" =~ ^[0-9]+$ ]] || [ "$FILE_NUMBER" -lt 1 ] || [ "$FILE_NUMBER" -gt "${#files[@]}" ]; then
    echo "Invalid selection."
    exit 1
fi

SELECTED_FILE="${files[$((file_number - 1))]}"
file_url="$BASE_URL$SUBJECT/$SELECTED_FILE"

curl -O "$file_url" || {
    echo "Failed to download file."
    exit 1
}

echo "File '$SELECTED_FILE' downloaded successfully."
