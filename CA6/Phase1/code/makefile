utms: main.o SystemController.o SystemOperator.o user.o student.o professor.o  major.o unit.o course.o date.o time.o CommandOperator.o exception.o method.o Post_method.o Get_method.o Put_method.o Delete_method.o
	g++ -std=c++20 main.o SystemController.o SystemOperator.o user.o student.o professor.o  major.o unit.o course.o date.o time.o CommandOperator.o exception.o method.o Post_method.o Get_method.o  Put_method.o Delete_method.o -o utms.out

main.o: main.cpp
	g++ -std=c++20 -c main.cpp

SystemController.o: SystemController.cpp
	g++ -std=c++20 -c SystemController.cpp

SystemOperator.o: SystemOperator.cpp
	g++ -std=c++20 -c SystemOperator.cpp

user.o: user.cpp
	g++ -std=c++20 -c user.cpp	

student.o: student.cpp
	g++ -std=c++20 -c student.cpp	

professor.o: professor.cpp
	g++ -std=c++20 -c professor.cpp

major.o: major.cpp
	g++ -std=c++20 -c major.cpp

unit.o: unit.cpp
	g++ -std=c++20 -c unit.cpp
	
course.o: course.cpp
	g++ -std=c++20 -c course.cpp

date.o: date.cpp
	g++ -std=c++20 -c date.cpp

time.o: time.cpp
	g++ -std=c++20 -c time.cpp

CommandOperator.o: CommandOperator.cpp
	g++ -std=c++20 -c CommandOperator.cpp

exception.o: exception.cpp
	g++ -std=c++20 -c exception.cpp

method.o: method.cpp
	g++ -std=c++20 -c method.cpp

Post_method.o: Post_method.cpp
	g++ -std=c++20 -c Post_method.cpp

Get_method.o: Get_method.cpp
	g++ -std=c++20 -c Get_method.cpp

Put_method.o: Put_method.cpp
	g++ -std=c++20 -c Put_method.cpp

Delete_method.o: Delete_method.cpp
	g++ -std=c++20 -c Delete_method.cpp

clean:
	rm *.o utms.out
