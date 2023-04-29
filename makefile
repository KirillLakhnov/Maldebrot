O_FLAGS := -Ofast
NO_DRAW_MODE := 

no_o: main.cpp maldebrot.cpp maldebrot_no.cpp
	g++ main.cpp maldebrot.cpp maldebrot_no.cpp -lsfml-graphics -lsfml-window -lsfml-system $(O_FLAGS) $(NO_DRAW_MODE) -DNO_O

sse: main.cpp maldebrot.cpp maldebrot_sse.cpp
	g++ main.cpp maldebrot.cpp maldebrot_sse.cpp -lsfml-graphics -lsfml-window -lsfml-system $(O_FLAGS) $(NO_DRAW_MODE) -DSSE

avx2: main.cpp maldebrot.cpp maldebrot_avx2.cpp
	g++ main.cpp maldebrot.cpp maldebrot_avx2.cpp -lsfml-graphics -lsfml-window -lsfml-system -mavx2 $(O_FLAGS) $(NO_DRAW_MODE) -DAVX2

avx512: main.cpp maldebrot.cpp maldebrot_avx512.cpp
	g++ main.cpp maldebrot.cpp maldebrot_avx512.cpp -lsfml-graphics -lsfml-window -lsfml-system -mavx512f $(O_FLAGS) $(NO_DRAW_MODE) -DAVX512
