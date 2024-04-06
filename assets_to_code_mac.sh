#!/bin/bash

# Define the source and destination directories
src_dir="src/assets"
output_dir="src"

# Define the output filenames
header_file="$output_dir/resources.h"
source_file="$output_dir/resources.c"

# Create or clear the output files
> "$header_file"
> "$source_file"

# Write the header file
echo "#ifndef RESOURCES_H" >> "$header_file"
echo "#define RESOURCES_H" >> "$header_file"
echo "" >> "$header_file"
echo "#include \"engine/include/hashtable.h\"" >> "$header_file"
echo "#include \"engine/include/assets.h\"" >> "$header_file"
echo "#include <string.h>" >> "$header_file"
echo "" >> "$header_file"
echo "HashTable* init_resources();" >> "$header_file"

# Write the source file
echo "#include \"resources.h\"" >> "$source_file"
echo "" >> "$source_file"

# Function to convert image file to C byte array
convert_to_byte_array() {
    local input_file="$1"
    #echo $input_file
    local xxd_output
    xxd_output=$(xxd -i "$input_file")
    #echo $xxd_output
    # Extract variable name from xxd output
    local variable_name
    variable_name=$(echo "$xxd_output" | ggrep -oP '(?<=unsigned char )\w*(?=\[\])')
    echo $variable_name
    # Define output variable name for both .c and .h files
    local output_variable="${variable_name}"
    local output_size="${variable_name}_len"

    # Write the header file
    echo "extern unsigned char $output_variable[];" >> "$header_file"
    echo "extern int $output_size;" >> "$header_file"
    echo "" >> "$header_file"

    # Remove const from the xxd output
    xxd_output=$(echo "$xxd_output" | sed 's/const//g')

    # Write the source file
    echo "$xxd_output" >> "$source_file"
    echo "" >> "$source_file"
}

# Find all image files in src/assets/ directory and its subdirectories
find "$src_dir" -type f \( -iname \*.jpg -o -iname \*.jpeg -o -iname \*.png -o -iname \*.bmp \) | while read -r file; do
    convert_to_byte_array "$file"
done

sed -i '' 's/unsigned int/int/g' "$source_file"

# Write the function to list all images and their sizes
echo "HashTable* init_resources(void) {" >> "$source_file"
echo "    HashTable* resources = createHashTable(10);" >> "$source_file"

# Add entries for each image
echo "" >> "$source_file"
echo "    // Add entries for each image" >> "$source_file"

# Loop through all image files again to add to init_resources function
find "$src_dir" -type f \( -iname \*.jpg -o -iname \*.jpeg -o -iname \*.png -o -iname \*.bmp \) | while read -r file; do
    file_extension="${file##*.}"
    file_name=$(basename "$file" ".$file_extension")
    echo "" >> "$source_file"
    echo "    char* src_assets_${file_name}_key = (char*)malloc(strlen(\"src_assets_${file_name}\")+1);" >> "$source_file"
    echo "    strcpy(src_assets_${file_name}_key, \"src_assets_${file_name}\");" >> "$source_file"
    echo "" >> "$source_file"
    echo "    MemTexture* src_assets_${file_name}_texture = (MemTexture*)malloc(sizeof(MemTexture));" >> "$source_file"
    echo "    src_assets_${file_name}_texture->data = src_assets_${file_name}_${file_extension};" >> "$source_file"
    echo "    src_assets_${file_name}_texture->size = src_assets_${file_name}_${file_extension}_len;" >> "$source_file"
    echo "    insert(resources, src_assets_${file_name}_key, src_assets_${file_name}_texture);" >> "$source_file"
    echo "" >> "$source_file"
done

echo "    return resources;" >> "$source_file"
echo "}" >> "$source_file"

# Write the closing of the header file
echo "#endif // RESOURCES_H" >> "$header_file"

# Add function prototype to header file
