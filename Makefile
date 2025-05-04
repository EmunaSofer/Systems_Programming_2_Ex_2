# emuna002@gmail.com

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g
DOCTEST_PATH = ./doctest.h

# קבצים רלוונטיים
SRC = SquareMat.cpp Test.cpp
OBJ = $(SRC:.cpp=.o)
EXE = bin/Main

# יצירת קובץ הדגמה
Main: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# בדיקות יחידה
test: $(OBJ)
	$(CC) $(CFLAGS) -o bin/test $(OBJ)
	./bin/test

# בדיקת זליגת זיכרון עם Valgrind
valgrind: $(OBJ)
	$(CC) $(CFLAGS) -o bin/test $(OBJ)
	valgrind --leak-check=full ./bin/test

# ניקוי קבצים לא רלוונטיים
clean:
	rm -f $(OBJ) $(EXE) bin/test
