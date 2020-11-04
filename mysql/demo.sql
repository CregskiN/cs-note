USE Student_info;
-- 1
CREATE PROCEDURE stu_pr() 
BEGIN
	IF @isDefined = 0 THEN
		SELECT '未创建';
		SELECT Student.*, SC.Cno, SC.Grade 
		FROM Student LEFT JOIN SC
		ON Student.Sno = SC.Sno;
	ELSEIF @isDefined = 1 THEN
		SELECT '已创建';
END $

-- 2.1
DROP PROCEDURE stu_proc1;
CREATE PROCEDURE stu_proc1(
	IN sdept CHAR(20),
	IN sname VARCHAR(8)
)
BEGIN
	SELECT Student.Sno, Student.Sname, (CURRENT_DATE - Student.Birth), SC_Course.Cname, SC_Course.Grade
	FROM Student LEFT JOIN (
		SELECT SC.Sno, Course.Cname, SC.Grade
		FROM SC LEFT JOIN Course
		ON SC.Cno = Course.Cno
	) AS SC_Course
	ON Student.Sno = SC_Course.Sno
	WHERE Student.Sname = sname AND Student.sdept = sdept;
END

DROP PROCEDURE stu_proc1;
CALL `stu_proc1`('计算机系', '刘雪魁');

SHOW ENGINES;