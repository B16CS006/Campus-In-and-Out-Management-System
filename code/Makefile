OBJS = account.o admin.o database.o faculty.o function.o institute.o institute_member.o person.o security.o student.o vehicle.o worker.o main.o
EXES = campus.out
FLAGS = -c
CC = g++

#all: campus
all: $(EXES)

campus.out: account.o admin.o database.o faculty.o function.o institute.o institute_member.o person.o security.o student.o vehicle.o worker.o main.o
	g++ account.o admin.o database.o faculty.o function.o institute.o institute_member.o person.o security.o student.o vehicle.o worker.o main.o -o campus.out
#campus: $(OBJS)
#	$(CC) $(OBJS) -o $(EXES)

clean:
	rm account.o admin.o database.o faculty.o function.o institute.o institute_member.o person.o security.o student.o vehicle.o worker.o main.o $(EXES)

#account.o: account.cpp
#	$(CC) $(FLAGS) account.cpp

account.o: account.cpp
	g++ -c account.cpp

admin.o: admin.cpp
	g++ -c admin.cpp

database.o: database.cpp
	g++ -c database.cpp

faculty.o: faculty.cpp
	g++ -c faculty.cpp

function.o: function.cpp
	g++ -c function.cpp

institute.o: institute.cpp
	g++ -c institute.cpp

institute_member.o: institute_member.cpp
	g++ -c institute_member.cpp

person.o: person.cpp
	g++ -c person.cpp

security.o: security.cpp
	g++ -c security.cpp

student.o: student.cpp
	g++ -c student.cpp

vehicle.o: vehicle.cpp
	g++ -c vehicle.cpp

worker.o: worker.cpp
	g++ -c worker.cpp

main.o: main.cpp
	g++ -c main.cpp

