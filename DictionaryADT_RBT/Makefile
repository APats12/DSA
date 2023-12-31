#------------------------------------------------------------------------------
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN2          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
SOURCE2        = $(MAIN2).cpp
OBJECT         = $(MAIN).o
OBJECT2        = $(MAIN).o
ADT_TEST       = $(ADT)Client
ADT_SELFTEST   = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN2): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(MAIN2) $(OBJECT2) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT_SELFTEST): $(ADT_SELFTEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_SELFTEST) $(ADT_SELFTEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_SELFTEST).o: $(ADT_SELFTEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_SELFTEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT_SELFTEST) $(MAIN2) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) GutenBerg.txt GutenBergout.txt

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
