PerMorf: src/Define.h src/Functions.h src/Types.h src/PerMorf.cpp
	g++ -Werror -Wall -O3 -I. src/PerMorf.cpp -o $@
