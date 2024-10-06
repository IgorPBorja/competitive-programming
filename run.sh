## compile and run c++ file with standard flags
## Usage: run.sh <filename>

# compile
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -D_GLIBCXX_DEBUG -fsanitize=address -fsanitize=undefined -fno-sanitize-recover $1 -o a.out

# run
./a.out

# remove executable
rm a.out

# flags meaning:
# -std=c++17: use c++17 standard
# -Wall: enable all warnings
# -Wextra: enable extra warnings
# -Wpedantic: enable pedantic warnings
# -Wshadow: warn the user if a variable declaration shadows one from a parent context
# -Wformat=2: warn about format strings that are not literals
# -Wfloat-equal: warn about comparing floating point numbers using ==
# -Wconversion: warn about implicit conversions that may alter a value
# -D_GLIBCXX_DEBUG: enable debugging mode
# -fsanitize=address: enable address sanitizer
# -fsanitize=undefined: enable undefined behavior sanitizer
# -fno-sanitize-recover: do not recover from sanitizer errors
