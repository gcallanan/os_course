# !/bin/bash
# A toy script to print out all the letters between two values. The script will
# also count out the number of 
#
# Remember to give this file execution permissions. Run:
#   "chmod +x printLetters.sh" in the terminal
# Run this script with ""./printLetters letterOne letterTwo" or with actual 
# values: "./printLetters c k"

echo "Shell Script To Print Letters"

# "$#"" is the number of arguments passed into the script. If this is not two, 
# print an error message and exit.
if [[ $# -ne 2 ]]; then
    echo "ERROR: We expected 2 arguments, we instead got $#."
    exit
fi

# Print out the parameters
echo "Input paramters $1 and $2"

# {a..f} will become the literal "a b c d e f" however {$1..$2} where these
# values equal a and f will return a string {a..f} that wont be expanded. We 
# force bash to interpret this using the eval command which will evaluate a
# string as shell code. This is why we have "for x in $(eval echo {$1..$2});"
# instead of "for x in {$1..$2};""
for x in $(eval echo {$1..$2});
do
    # Find the names of files in this directory that have the letter $x in 
    # their name, then pipe this output to wc. "wc -l" will count the number of
    # lines returned by this command
    numFiles=$(find . -name "*$x*" -print | wc -l);
    
    # Print out the file and the number of files where the letter appears in
    # the name
    echo "$x:$numFiles" 
done

# If you want to run this script and then ignore all the letters that have zero
# files mapped through them, consider piping it to grep: 
#   ./printLetters.sh a z | grep -v "[0]"


