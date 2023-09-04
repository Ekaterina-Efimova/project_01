CREATE TABLE Students
(
	Student_Id Integer NOT NULL, 
	Student_Name Text NOT NULL, 
	School_Id Integer PRIMARY KEY
);
INSERT INTO Students
VALUES
	(201, 'Иван', 1),
	(202, 'Петр', 2),
	(203, 'Анастасия', 3),
	(204, 'Игорь', 4);
SELECT Student_Id, Student_Name, School.School_Id, School_Name
FROM  Students
INNER JOIN School on School.School_Id = Students.School_Id