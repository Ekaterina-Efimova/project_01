import sqlite3
con = sqlite3.connect('teatchers.db')
cur = con.cursor()
cre = """CREATE TABLE Students
(
	Student_Id Integer NOT NULL, 
	Student_Name Text NOT NULL, 
	School_Id Integer PRIMARY KEY
)"""
ins = """INSERT INTO Students
VALUES
	(201, 'Иван', 1),
	(202, 'Петр', 2),
	(203, 'Анастасия', 3),
	(204, 'Игорь', 4);"""
sel = """SELECT Student_Id, Student_Name, School.School_Id, School_Name
FROM  Students
INNER JOIN School on School.School_Id = Students.School_Id """
cur. execute (cre)
cur.execute (ins)
cur.execute (sel)
a=cur.fetchall()

for i in a:
    print ("ID student", i[0])
    print ("Sudent's name", i[1])
    print ("ID school", i[2])
    print ("school's name", i[3])


