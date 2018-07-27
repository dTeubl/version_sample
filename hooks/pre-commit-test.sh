# This a test-file for pre-commit hook
# To make this work, run the "make hooks" command in the main project directory

echo "Start of the Pre-commit hook!"

git status

./run.sh

git status

git add -A

git status

./fwid

echo "End of the Pre-commit hook!"

