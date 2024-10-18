#!/bin/bash

echo "Enter subject (DAA/ML/BT): "
read -r SUBJECT

BASE_URL="https://api.github.com/repos/shxntanu/BE-Lab-Assignments/contents/"

case "$SUBJECT" in
"DAA" | "ML" | "BT")
    SUBJECT_URL="${BASE_URL}${SUBJECT}"
    ;;
*)
    echo "Invalid subject name. Please choose from DAA, ML, or BT."
    exit 1
    ;;
esac

RESPONSE=$(curl -s "$SUBJECT_URL")

# Check if the response contains files
if [[ "$RESPONSE" == *"Not Found"* ]]; then
    echo "Directory not found on GitHub."
    exit 1
fi

# Parse the file names from the GitHub API response using `jq`
files=($(echo "$RESPONSE" | jq -r '.[].name'))

echo "Files in the $SUBJECT directory on GitHub:"
for i in "${!files[@]}"; do
    echo "$((i + 1)). ${files[i]}"
done

echo "Enter the number of the file you want to download:"
read -r FILE_NUMBER

if ! [[ "$FILE_NUMBER" =~ ^[0-9]+$ ]] || [ "$FILE_NUMBER" -lt 1 ] || [ "$FILE_NUMBER" -gt "${#files[@]}" ]; then
    echo "Invalid selection."
    exit 1
fi

SELECTED_FILE="${files[$((FILE_NUMBER - 1))]}"
file_url="https://raw.githubusercontent.com/shxntanu/BE-Lab-Assignments/main/$SUBJECT/$SELECTED_FILE"

wget -qO- "$file_url" || {
    echo "Failed to download file."
    exit 1
}

echo "File '$SELECTED_FILE' downloaded successfully."
