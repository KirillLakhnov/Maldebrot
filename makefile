no_o: main.cpp maldebrot.cpp maldebrot_no.cpp
	g++ main.cpp maldebrot.cpp maldebrot_no.cpp -lsfml-graphics -lsfml-window -lsfml-system -Ofast -DNO_O

sse: main.cpp maldebrot.cpp maldebrot_sse.cpp
	g++ main.cpp maldebrot.cpp maldebrot_sse.cpp -lsfml-graphics -lsfml-window -lsfml-system -Ofast -DSSE

avx2: main.cpp maldebrot.cpp maldebrot_avx2.cpp
	g++ main.cpp maldebrot.cpp maldebrot_avx2.cpp -lsfml-graphics -lsfml-window -lsfml-system -mavx2 -Ofast -DAVX2

avx512: main.cpp maldebrot.cpp maldebrot_avx512.cpp
	g++ main.cpp maldebrot.cpp maldebrot_avx512.cpp -lsfml-graphics -lsfml-window -lsfml-system -mavx512f -Ofast -DAVX512
