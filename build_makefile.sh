#!/bin/bash

fconfig="config"
configdir=$1
if [ "$1" == "" ]; then
    configdir="."
fi

if [[ -f "$configdir/config" ]]; then
    printf ""
else
    echo "auto-makefile: no config file found in directory '$configdir'"
    exit 1
fi

LIBPOS=$(awk -F ';' '$1 == "LIB_POS" {print $2}' $fconfig)
lb="-L$LIBPOS"
inc="-I./"
objprefix="$(awk -F ';' '$1 == "OBJ_DIR" {print $2}' $fconfig)"
if [ "$objprefix" == "" ]; then
    objprefix="obj"
fi

opti="-O3 -Ofast \\
-ftree-vectorize \\
-ftree-loop-distribution -funroll-all-loops -funswitch-loops \\
-march=native -mtune=native -fopenmp -mavx2 \\
-lm -ffast-math -mfpmath=sse \\
-fno-builtin"

function header()
{
    projectname=$(basename "$(pwd)" | cut -d- -f7)
    if [ "$projectname" == "" ]; then
        projectname=$(basename "$(pwd)")
    fi
    {
      echo "##";
      echo "## EPITECH PROJECT, 20$(date +%y)";
      echo "## Makefile $projectname";
      echo "## File description:";
      echo "## Makefile";
      echo -e "##\n";
    } > Makefile
}

header
SOURCES=$(awk -F ';' '$1 == "SOURCES_DIR" {print $2}' $fconfig)
NBDIRS=$(echo "$SOURCES" | sed -e 's/\(.\)/\1\n/g' | grep -c ' ')
echo -e "SOURCES = $SOURCES\n" >> Makefile
echo -e 'SRCS =' | tr "\n" " " >> Makefile
for i in $(seq 0 "$NBDIRS"); do
    CURRDIR=$(echo "$SOURCES" | cut -d ' ' -f$((i + 1)))
    for FILE in "$CURRDIR"/*; do
        if [[ $FILE =~ \.c ]]; then
            if [[ $FILE =~ \./ ]]; then
                echo -e "\t$FILE\t\\" | sed -e 's/\.\///g'>> Makefile
            else
                echo -e "\t$FILE\t\\" >> Makefile
            fi
        fi
    done
done

printf "\nOBJS = " >> Makefile
for i in $(seq 0 "$NBDIRS"); do
    CURRDIR=$(echo "$SOURCES" | cut -d ' ' -f$((i + 1)))
    for FILE in "$CURRDIR"/*; do
        if [[ $FILE =~ \.c ]]; then
            if [[ $FILE =~ \./ ]]; then
                echo -e "\t$objprefix/$(basename "$FILE" | sed "s/\.c/.o/g")\t\\" >> Makefile
            else
                echo -e "\t$objprefix/$(basename "$(echo "$FILE" | tr '/' '-')" | sed "s/\.c/.o/g")\t\\" >> Makefile
            fi
        fi
    done
done

{
echo -e "\nOBJ_DIR = $objprefix";
# shellcheck disable=SC2016
echo -e '\nOBJ = $(SRCS:%.c=obj/%.o)\n';
echo -e "OPTI = $opti\n";
echo -e "# \tOptimization flags:\n
# -O3: Enables all optimizations that do not involve a space-speed tradeoff.
# -Ofast: Enables all optimizations allowed by the language standard,
# \tincluding potentially unsafe ones.\n
# \tVectorization flags:\n
# -fopt-info-vec -all-ftree-vectorize: Provides information about vectorization
# \tand tree vectorization.\n
# \tLoop unrolling flags:\n
# -ftree-loop-distribution: Distributes loop iterations over multiple threads.
# -funroll-loops: Unrolls loops to reduce loop overhead.
# -funroll-all-loops: Unrolls all loops, regardless of their size.
# -funswitch-loops: Enables loop inversion for better instruction scheduling.\n
# \tCPU-specific flags:\n
# -march=native: Generates code optimized for the host machine architecture.
# -mtune=native: Generates code optimized for the host machine CPU.
# -fopenmp: Enables OpenMP parallelization.
# -mavx2: Enables use of Advanced Vector Extensions 2.\n
# \tLinker flags:\n
# -lm: Links the math library.
# -ffast-math: Enables fast math operations, which may not be IEEE compliant.
# -mfpmath=sse: Uses SSE instructions for floating-point math.\n
# \tLink-time optimization flags:\n
# -flto: Enables link-time optimization, which allows the compiler to optimize
# \tacross object files.\n";
echo -e "NAME  = $(awk -F ';' '$1 == "EXEC" {print $2}' $fconfig)\n";
echo -e "CC  = $(awk -F ';' '$1 == "CC" {print $2}' $fconfig)\n";
printf 'LIB = %s' "$lb";
} >> Makefile
LIBS=$(awk -F ';' '$1 == "LIBS_DIR" {print $2}' $fconfig)
NBLIBS=$(echo "$LIBS" | wc -w)
for i in $(seq 1 "$NBLIBS"); do
    CURRLIB=$(echo "$LIBS" | cut -d ' ' -f$((i + 1)))
    libfield=1
    while [ "$(echo "$CURRLIB" | cut -d/ -f$libfield)" != "" ]; do
        libfield=$((libfield + 1))
    done
    if [ $libfield -ne 1 ]; then
        echo -e "\t-l$(echo "$CURRLIB" | cut -d/ -f$((libfield - 1)))\t\\" >> Makefile
    fi
done


HEADERS=$(awk -F ';' '$1 == "HEADERS_DIR" {print $2}' $fconfig)
printf "\nHEADER = " >> Makefile
NBHEADERS=$(echo "$HEADERS" | wc -w)
for i in $(seq 0 $((NBHEADERS - 1))); do
    CURRHEADER=$(echo "$HEADERS" | cut -d ' ' -f$((i + 1)))
    echo -e "\t$inc$CURRHEADER\t\\" >> Makefile
done

{
printf '\nCFLAGS += %s' "$(awk -F ';' '$1 == "CFLAGS" {print $2}' $fconfig)";
# shellcheck disable=SC2016
echo -e ' \\\n\t$(LIB) $(HEADER)\n';
echo -e "DEBUGFLAGS += $(awk -F ';' '$1 == "DEBUGFLAGS" {print $2}' $fconfig)" | tr "\n" " ";
# shellcheck disable=SC2016
echo -e '\\\n\t$(LIB) $(HEADER) -ggdb\n';
# shellcheck disable=SC2016
echo -e 'all: $(NAME)\n';
# shellcheck disable=SC2016
echo -e '$(OBJ_DIR)/%.o: %.c\n\t@$(CC) $(CFLAGS) -c $< -o \\\n$(addprefix $(OBJ_DIR)/, $(basename $(subst /,-,$<)).o)\n';
# shellcheck disable=SC2016
echo -e '$(NAME): $(OBJ)';
} >> Makefile
if [ "$NBLIBS" -ne 0 ]; then
    for i in $(seq 1 "$NBLIBS"); do
        CURRLIB="$(echo "$LIBS" | cut -d ' ' -f$((i + 1)))"
        echo -e "\t@make -s -C $LIBPOS/$CURRLIB">> Makefile
    done
fi
{
# shellcheck disable=SC2016
echo -e '\t@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)\n\t@echo -e "\033[1;32mProject built successfully\033[0m"\n';
# shellcheck disable=SC2016
echo -e 'debug:\tclean\n\t@$(CC) $(SRCS) -o $(NAME) $(DEBUGFLAGS)\n\t@echo -e "\033[1;33mProject built in debug mode\033[0m"\n';
# shellcheck disable=SC2016
echo -e 'clean:\n\t@rm $(OBJS) .idea/ -rf\n\t@rm *.gcno -rf\n\t@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete\n\t@find . -type f,d -name "vgcore*" -delete\n\t@echo -e "\033[1;34mRepo cleaned\033[0m"\n';
# shellcheck disable=SC2016
echo -e 'fclean: clean\n\t@rm $(NAME) -rf\n\t@find . -type f,d -name "*.a" -delete\n\t@echo -e "\033[1;31mProject binary deleted\033[0m"\n';
# shellcheck disable=SC2016
echo -e 're: fclean $(NAME)\n'>> Makefile
# shellcheck disable=SC2016
echo '.PHONY: all $(NAME) clean fclean re';
} >> Makefile
