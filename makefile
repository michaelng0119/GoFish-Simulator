# target: dependencies
# <tab> rule
#
# make (without arguments) executes first rule in file
#

GoFish : go_fish.o deck.o card.o player.o
	g++ -o GoFish go_fish.o deck.o card.o player.o
go_fish.o: go_fish.cpp deck.h card.h player.h
	g++ -c go_fish.cpp
deck.o: deck.cpp card.h
	g++ -c deck.cpp
player.o: player.cpp card.h
	g++ -c player.cpp
card.o: card.cpp card.h
	g++ -c card.cpp


