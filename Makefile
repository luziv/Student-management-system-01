student = main.o studentmgr.o student.o login.o tool.o

student : $(student)
	g++ -o student $(student)

main.o : student.h
studentmgr.o : studentmgr.h tool.h
student.o : student.h
login.o : login.h student.h tool.h
tool.o : tool.h login.h

.PHONY:clean
clean:
	rm student $(student)

